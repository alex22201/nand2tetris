#include "assembler.h"

#include "instructions.h"
#include "parser.h"
#include "symbol_table.h"

static ssize_t program_counter = 0;
static ssize_t free_register_number = 16;

/* Removes spaces and new line characters from string */
static void remove_spaces(char* str) {
  char* d = str;
  do {
    while (*d == ' ' || *d == '\n' || *d == '\r') {
      ++d;
    }

  } while ((*str++ = *d++));
}

/* Removes comments starting with '//' from string */
static void remove_comments(char* str) {
  size_t length = strlen(str);
  for (size_t i = 0; i < length; ++i) {
    if (str[i] == '/') {
      if (str[i + 1] == '/') {
        str[i] = '\0';
        return;
      } else {
        fprintf(stderr,
                "Incorrect comment in line %zu:\n%s\n"
                "Correct format:\n// Comment example\n",
                program_counter, str);
        exit(EXIT_FAILURE);
      }
    }
  }
}

/* Prepares assembler instruction to assembling */
static void format_asm_instruction(char* asm_instruction) {
  remove_comments(asm_instruction);
  remove_spaces(asm_instruction);
}

/* Calculates if a string is a number */
static bool is_number(const char* str) {
  if (str == NULL) return false;

  for (int i = 0; str[i] != '\0'; ++i) {
    if (!isdigit(str[i])) return false;
  }
  return true;
}

/* Creates C-instruction structure from formatted assembler instruction */
struct CInstruction assemble_c_instruction(const char* asm_instruction) {
  assert(asm_instruction);
  struct CInstructionDest dest;
  struct CInstructionJump jump;
  struct CInstructionComp comp;

  char* asm_dest_instruction = divide_c_instruction_dest(asm_instruction);
  dest = create_c_instruction_dest(asm_dest_instruction);
  free(asm_dest_instruction);

  char* asm_jump_instruction = divide_c_instruction_jump(asm_instruction);
  jump = create_c_instruction_jump(asm_jump_instruction);
  free(asm_jump_instruction);

  char* asm_comp_instruction = divide_c_instruction_comp(asm_instruction);
  comp = create_c_instruction_comp(asm_comp_instruction);
  free(asm_comp_instruction);

  struct CInstruction instruction = create_c_instruction(comp, dest, jump);

  return instruction;
}

/* Creates A-instruction structure from formatted assembler instruction */
struct AInstruction assemble_a_instruction(const char* asm_instruction,
                                           ht_hash_table_t* symbol_table) {
  struct AInstruction a_instruction;

  if (!asm_instruction || strlen(asm_instruction) < 2 ||
      asm_instruction[0] != '@') {
    fprintf(stderr, "Incorrect A-instruction in line %zu:\n%s", program_counter,
            asm_instruction);
    exit(EXIT_FAILURE);
  }

  ++asm_instruction;

  if (is_number(asm_instruction)) {
    ht_value_t value = strtol(asm_instruction, NULL, 10);
    a_instruction = create_a_instruction(value);
  } else {
    // search variable in table
    ht_value_t variable_value = ht_search(symbol_table, asm_instruction);

    if (variable_value != -1)
      a_instruction = create_a_instruction(variable_value);
    else {
      ht_insert(symbol_table, asm_instruction, free_register_number);
      a_instruction = create_a_instruction(free_register_number);
      ++free_register_number;
    }
  }

  return a_instruction;
}

/* 
  Parses assembler instruction and determines if it is a label or not.
  Return  1 if it's correct instruction
          0 if it's not a label
         -1 if it's incorrect instruction
*/
static int is_label(const char* asm_instruction) {
  size_t instruction_size = strlen(asm_instruction);

  if (asm_instruction[0] == '(' &&
      asm_instruction[instruction_size - 1] == ')') {
    return true;
  } else if ((asm_instruction[0] == '(' &&
              asm_instruction[instruction_size - 1] != ')') ||
             (asm_instruction[0] != '(' &&
              asm_instruction[instruction_size - 1] == ')')) {
    return -1;
  }

  return false;
}

/* Fill symbol table with labels */
void make_first_pass(FILE* input_f, ht_hash_table_t* symbol_table) {
  rewind(input_f);
  char* asm_instruction = NULL;
  size_t buf_size = 0;
  program_counter = 0;

  /* Loop through until we are done with the file. */
  while (getline(&asm_instruction, &buf_size, input_f) != -1) {
    format_asm_instruction(asm_instruction);
    size_t instruction_size = strlen(asm_instruction);
    if (!instruction_size) continue;

    // Parse label
    int label_correct = is_label(asm_instruction);
    if (label_correct == -1) {
      fprintf(stderr, "Incorrect label in line %zu:\n%s", program_counter,
              asm_instruction);
      exit(EXIT_FAILURE);
    } else if (label_correct) {
      asm_instruction[instruction_size - 1] = '\0';
      ht_insert(symbol_table, asm_instruction + 1, program_counter);

      continue;
    }

    ++program_counter;
  }

  free(asm_instruction);
}

/* Creates instructions and prints binary equivalent to the output file */
void make_second_pass(FILE* input_f, FILE* output_f,
                      ht_hash_table_t* symbol_table) {
  rewind(input_f);
  char* asm_instruction = NULL;
  size_t buf_size = 0;

  /* Loop through until we are done with the file. */
  while (getline(&asm_instruction, &buf_size, input_f) != -1) {
    format_asm_instruction(asm_instruction);
    size_t instruction_size = strlen(asm_instruction);

    if (!instruction_size) continue;
    if (is_label(asm_instruction)) continue;

    if (asm_instruction[0] == '@') {  // A-instruction
      struct AInstruction instruction =
          assemble_a_instruction(asm_instruction, symbol_table);
      fprint_a_instruction(output_f, &instruction);
    } else {  // C-instruction
      struct CInstruction instruction = assemble_c_instruction(asm_instruction);
      fprint_c_instruction(output_f, &instruction);
    }
  }

  free(asm_instruction);
}

/* Counts the number of lines in a file */
static size_t count_lines(FILE* file) {
  size_t buf_size = 65536;
  char line[buf_size];
  size_t count = 1;

  while (!feof(file)) {
    size_t res = fread(line, 1, buf_size, file);
    for (size_t i = 0; i < res; ++i) {
      if (line[i] == '\n') ++count;
    }
  }

  return count;
}

/* Translates assembler instructions from input_f to binary code in output_f */
void assemble(FILE* input_f, FILE* output_f) {
  assert(input_f);
  assert(output_f);
  size_t lines_count = count_lines(input_f);
  ht_hash_table_t* symbol_table = create_symbol_table(lines_count);

  make_first_pass(input_f, symbol_table);
  make_second_pass(input_f, output_f, symbol_table);
}
