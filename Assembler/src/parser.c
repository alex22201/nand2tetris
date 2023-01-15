/* 
  Implements parsing assembler instructions and separating
  the required block from the instruction.
*/
#include "parser.h"

#include <stdlib.h>
#include <string.h>

/* 
  Searches for the first occurrence of a ch character in a string str.
  Return -1 if there is no such character.
*/
static int get_char_pos(const char* str, char ch) {
  for (int i = 0; i < strlen(str); ++i) {
    if (str[i] == ch) return i;
  }
  return -1;
}

/* 
  Parses full assembler C-instruction and extracts Destination part from it.
  Return Destination instruction part.
*/
char* divide_c_instruction_dest(const char* asm_instruction) {
  // check if dest exists
  ssize_t equals_pos = get_char_pos(asm_instruction, '=');
  size_t elem_count = 1;  // one char for '\0'
  if (equals_pos != -1) elem_count = equals_pos + 1;

  // create string with dest instruction
  char* asm_dest_instruction = malloc(sizeof(char) * elem_count);
  for (int i = 0; i < equals_pos; ++i) {
    asm_dest_instruction[i] = asm_instruction[i];
  }

  return asm_dest_instruction;
}

/* 
  Parses full assembler C-instruction and extracts Jump part from it.
  Return Jump instruction part.
*/
char* divide_c_instruction_jump(const char* asm_instruction) {
  // check if jmp exists
  ssize_t semicolon_pos = get_char_pos(asm_instruction, ';');
  size_t elem_count = 1;  // one char for '\0'
  if (semicolon_pos != -1)
    elem_count = strlen(asm_instruction) - semicolon_pos + 1;

  // create string with jump instruction
  ssize_t asm_instruction_pos;
  char* asm_jump_instruction = malloc(sizeof(char) * elem_count);
  if (semicolon_pos != -1) {
    asm_instruction_pos = semicolon_pos + 1;
    for (int i = 0; asm_instruction_pos < strlen(asm_instruction); ++i) {
      asm_jump_instruction[i] = asm_instruction[asm_instruction_pos];
      ++asm_instruction_pos;
    }
  }

  return asm_jump_instruction;
}

/* 
  Parses full assembler C-instruction and extracts Computation part from it.
  Return Computation instruction part.
*/
char* divide_c_instruction_comp(const char* asm_instruction) {
  ssize_t semicolon_pos = get_char_pos(asm_instruction, ';');
  ssize_t equals_pos = get_char_pos(asm_instruction, '=');
  ssize_t asm_instruction_pos;
  size_t elem_count;

  // parse comp
  size_t end = strlen(asm_instruction);
  ssize_t comp_start = equals_pos == -1 ? 0 : equals_pos + 1;
  if (semicolon_pos != -1) {
    end = semicolon_pos;
    elem_count = semicolon_pos - comp_start + 1;
  } else {
    elem_count = end - comp_start + 1;  // 1 char for '\0'
  }
  char* asm_comp_instruction = malloc(sizeof(char) * elem_count);

  asm_instruction_pos = comp_start;
  for (int i = 0; asm_instruction_pos < end; ++i) {
    asm_comp_instruction[i] = asm_instruction[asm_instruction_pos];
    ++asm_instruction_pos;
  }

  return asm_comp_instruction;
}

