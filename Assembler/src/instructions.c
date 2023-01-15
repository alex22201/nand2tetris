/* Creating instruction structures from parsed assembler instruciton strings */
#include "instructions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Converts decimal integer in A-instruction to binary form in struct field */
static void convert_a_instruction_to_binary(struct AInstruction* instruction) {
  int value = instruction->value;
  int bits_count = 15;  // bits count
  for (int i = bits_count - 1; i >= 0; --i) {
    instruction->binary_value[i] = (value % 2) + 48;
    value /= 2;
  }
  instruction->binary_value[bits_count] = '\0';
}

/* Creates A-instruction from decimal integer value */
struct AInstruction create_a_instruction(ht_value_t value) {
  struct AInstruction instruction;
  instruction.instruction_bit = '0';
  instruction.value = value;
  convert_a_instruction_to_binary(&instruction);
  return instruction;
}

/* Parsing Computation instruction to create enum object of computation type */
static enum CompOperation parse_c_instruction_comp(
    const char* asm_comp_instruction) {
  if (strcmp(asm_comp_instruction, "0") == 0) {
    return Zero;
  } else if (strcmp(asm_comp_instruction, "1") == 0) {
    return One;
  } else if (strcmp(asm_comp_instruction, "-1") == 0) {
    return MinusOne;
  } else if (strcmp(asm_comp_instruction, "D") == 0) {
    return DRegister;
  } else if (strcmp(asm_comp_instruction, "A") == 0) {
    return ARegister;
  } else if (strcmp(asm_comp_instruction, "!D") == 0) {
    return NotDRegister;
  } else if (strcmp(asm_comp_instruction, "!A") == 0) {
    return NotARegister;
  } else if (strcmp(asm_comp_instruction, "-D") == 0) {
    return MinusDRegister;
  } else if (strcmp(asm_comp_instruction, "-A") == 0) {
    return MinusARegister;
  } else if (strcmp(asm_comp_instruction, "D+1") == 0) {
    return DRegisterPlusOne;
  } else if (strcmp(asm_comp_instruction, "A+1") == 0) {
    return ARegisterPlusOne;
  } else if (strcmp(asm_comp_instruction, "D-1") == 0) {
    return DRegisterMinusOne;
  } else if (strcmp(asm_comp_instruction, "A-1") == 0) {
    return ARegisterMinusOne;
  } else if (strcmp(asm_comp_instruction, "D+A") == 0) {
    return DRegisterPlusARegister;
  } else if (strcmp(asm_comp_instruction, "D-A") == 0) {
    return DRegisterMinusARegister;
  } else if (strcmp(asm_comp_instruction, "A-D") == 0) {
    return ARegisterMinusDRegister;
  } else if (strcmp(asm_comp_instruction, "D&A") == 0) {
    return DRegisterAndARegister;
  } else if (strcmp(asm_comp_instruction, "D|A") == 0) {
    return DRegisterOrARegister;
  } else if (strcmp(asm_comp_instruction, "M") == 0) {
    return RAM;
  } else if (strcmp(asm_comp_instruction, "!M") == 0) {
    return NotRAM;
  } else if (strcmp(asm_comp_instruction, "-M") == 0) {
    return MinusRAM;
  } else if (strcmp(asm_comp_instruction, "M+1") == 0) {
    return RAMPlusOne;
  } else if (strcmp(asm_comp_instruction, "M-1") == 0) {
    return RAMMinusOne;
  } else if (strcmp(asm_comp_instruction, "D+M") == 0) {
    return DRegisterPlusRAM;
  } else if (strcmp(asm_comp_instruction, "D-M") == 0) {
    return DRegisterMinusRAM;
  } else if (strcmp(asm_comp_instruction, "M-D") == 0) {
    return RAMMinusDRegister;
  } else if (strcmp(asm_comp_instruction, "D&M") == 0) {
    return DRegisterAndRAM;
  } else if (strcmp(asm_comp_instruction, "D|M") == 0) {
    return DRegisterOrRAM;
  }

  fprintf(stderr, "Unknown COMP instruction:\n%s", asm_comp_instruction);
  exit(EXIT_FAILURE);
}

/* Fills a string with the values from another string */
static void assign_str(char* array, char* value) {
  for (int i = 0; i < strlen(value); ++i) {
    array[i] = value[i];
  }
}

/* Converts Computation enum object in C-instruction to binary form in struct
 * field */
static void convert_c_comp_operation_to_binary(
    struct CInstructionComp* instruction_comp) {
  switch (instruction_comp->operation) {
    case Zero:
      assign_str(instruction_comp->binary, "0101010");
      break;
    case One:
      assign_str(instruction_comp->binary, "0111111");
      break;
    case MinusOne:
      assign_str(instruction_comp->binary, "0111010");
      break;
    case DRegister:
      assign_str(instruction_comp->binary, "0001100");
      break;
    case ARegister:
      assign_str(instruction_comp->binary, "0110000");
      break;
    case NotDRegister:
      assign_str(instruction_comp->binary, "0001101");
      break;
    case NotARegister:
      assign_str(instruction_comp->binary, "0110001");
      break;
    case MinusDRegister:
      assign_str(instruction_comp->binary, "0001111");
      break;
    case MinusARegister:
      assign_str(instruction_comp->binary, "0110011");
      break;
    case DRegisterPlusOne:
      assign_str(instruction_comp->binary, "0011111");
      break;
    case ARegisterPlusOne:
      assign_str(instruction_comp->binary, "0110111");
      break;
    case DRegisterMinusOne:
      assign_str(instruction_comp->binary, "0001110");
      break;
    case ARegisterMinusOne:
      assign_str(instruction_comp->binary, "0110010");
      break;
    case DRegisterPlusARegister:
      assign_str(instruction_comp->binary, "0000010");
      break;
    case DRegisterMinusARegister:
      assign_str(instruction_comp->binary, "0010011");
      break;
    case ARegisterMinusDRegister:
      assign_str(instruction_comp->binary, "0000111");
      break;
    case DRegisterAndARegister:
      assign_str(instruction_comp->binary, "0000000");
      break;
    case DRegisterOrARegister:
      assign_str(instruction_comp->binary, "0010101");
      break;
    case RAM:
      assign_str(instruction_comp->binary, "1110000");
      break;
    case NotRAM:
      assign_str(instruction_comp->binary, "1110001");
      break;
    case MinusRAM:
      assign_str(instruction_comp->binary, "1110011");
      break;
    case RAMPlusOne:
      assign_str(instruction_comp->binary, "1110111");
      break;
    case RAMMinusOne:
      assign_str(instruction_comp->binary, "1110010");
      break;
    case DRegisterPlusRAM:
      assign_str(instruction_comp->binary, "1000010");
      break;
    case DRegisterMinusRAM:
      assign_str(instruction_comp->binary, "1010011");
      break;
    case RAMMinusDRegister:
      assign_str(instruction_comp->binary, "1000111");
      break;
    case DRegisterAndRAM:
      assign_str(instruction_comp->binary, "1000000");
      break;
    case DRegisterOrRAM:
      assign_str(instruction_comp->binary, "1010101");
      break;
    default:
      fprintf(stderr, "Unknown COMP operation!\n");
      exit(EXIT_FAILURE);
  }
  instruction_comp->binary[7] = '\0';
}

/* Creates Computation part of C-instruction */
struct CInstructionComp create_c_instruction_comp(
    const char* asm_comp_instruction) {
  struct CInstructionComp instruction_comp;
  instruction_comp.operation = parse_c_instruction_comp(asm_comp_instruction);
  convert_c_comp_operation_to_binary(&instruction_comp);
  return instruction_comp;
}

/* Parsing formatted assembler instruction to create Jump part 
 * of C-instruction */
static struct CInstructionJump parse_c_instruction_jump(
    const char* asm_jump_instruction) {
  struct CInstructionJump instruction_jump;

  if (strcmp(asm_jump_instruction, "JGT") == 0) {
    instruction_jump.greater = true;
    instruction_jump.equal = false;
    instruction_jump.lower = false;
  } else if (strcmp(asm_jump_instruction, "JEQ") == 0) {
    instruction_jump.greater = false;
    instruction_jump.equal = true;
    instruction_jump.lower = false;
  } else if (strcmp(asm_jump_instruction, "JGE") == 0) {
    instruction_jump.greater = true;
    instruction_jump.equal = true;
    instruction_jump.lower = false;
  } else if (strcmp(asm_jump_instruction, "JLT") == 0) {
    instruction_jump.greater = false;
    instruction_jump.equal = false;
    instruction_jump.lower = true;
  } else if (strcmp(asm_jump_instruction, "JNE") == 0) {
    instruction_jump.greater = true;
    instruction_jump.equal = false;
    instruction_jump.lower = true;
  } else if (strcmp(asm_jump_instruction, "JLE") == 0) {
    instruction_jump.greater = false;
    instruction_jump.equal = true;
    instruction_jump.lower = true;
  } else if (strcmp(asm_jump_instruction, "JMP") == 0) {
    instruction_jump.greater = true;
    instruction_jump.equal = true;
    instruction_jump.lower = true;
  } else if (strcmp(asm_jump_instruction, "") == 0) {
    instruction_jump.greater = false;
    instruction_jump.equal = false;
    instruction_jump.lower = false;
  } else {
    fprintf(stderr, "Unknown JUMP instruction:\n%s", asm_jump_instruction);
    exit(EXIT_FAILURE);
  }
  instruction_jump.binary[3] = '\0';

  return instruction_jump;
}

/* Converts Jump part in C-instruction to binary form in struct
 * field */
static void convert_c_jump_to_binary(
    struct CInstructionJump* instruction_jump) {
  instruction_jump->binary[0] = instruction_jump->lower ? '1' : '0';
  instruction_jump->binary[1] = instruction_jump->equal ? '1' : '0';
  instruction_jump->binary[2] = instruction_jump->greater ? '1' : '0';
}

/* Creates Jump part of C-instruction */
struct CInstructionJump create_c_instruction_jump(
    const char* asm_jump_instruction) {
  struct CInstructionJump instruction_jump =
      parse_c_instruction_jump(asm_jump_instruction);
  convert_c_jump_to_binary(&instruction_jump);

  return instruction_jump;
}

/* Parsing formatted assembler instruction to create Destination part 
 * of C-instruction */
static struct CInstructionDest parse_c_instruction_dest(
    const char* asm_dest_instruction) {
  struct CInstructionDest instruction_dest = {false};

  for (int i = 0; i < strlen(asm_dest_instruction); ++i) {
    switch (asm_dest_instruction[i]) {
      case 'M':
        instruction_dest.ram = true;
        break;
      case 'D':
        instruction_dest.d_register = true;
        break;
      case 'A':
        instruction_dest.a_register = true;
        break;
      default:
        fprintf(stderr, "Unknown DEST instruction:\n%s", asm_dest_instruction);
        exit(EXIT_FAILURE);
    }
  }

  return instruction_dest;
}

/* Converts Destination part in C-instruction to binary form in struct
 * field */
static void convert_c_dest_to_binary(
    struct CInstructionDest* instruction_dest) {
  instruction_dest->binary[0] = instruction_dest->a_register ? '1' : '0';
  instruction_dest->binary[1] = instruction_dest->d_register ? '1' : '0';
  instruction_dest->binary[2] = instruction_dest->ram ? '1' : '0';
  instruction_dest->binary[3] = '\0';
}

/* Creates Destination part of C-instruction */
struct CInstructionDest create_c_instruction_dest(
    const char* asm_dest_instruction) {
  struct CInstructionDest instruction_dest =
      parse_c_instruction_dest(asm_dest_instruction);
  convert_c_dest_to_binary(&instruction_dest);

  return instruction_dest;
}

/* Creates Fixed part of C-instruction */
static struct CInstructionFixed create_c_instruction_fixed() {
  struct CInstructionFixed instruction_fixed;
  instruction_fixed.binary[0] = '1';
  instruction_fixed.binary[1] = '1';
  instruction_fixed.binary[2] = '\0';

  return instruction_fixed;
}

/* Creates C-instruction from prepared parts (Comp, Dest, Jump) */
struct CInstruction create_c_instruction(struct CInstructionComp comp,
                                         struct CInstructionDest dest,
                                         struct CInstructionJump jump) {
  struct CInstruction instruction;
  instruction.instruction_bit = '1';
  instruction.fixed = create_c_instruction_fixed();
  instruction.comp = comp;
  instruction.dest = dest;
  instruction.jump = jump;

  return instruction;
}

/* Prints A-instrution in binary form to file */
void fprint_a_instruction(FILE* stream,
                          const struct AInstruction* instruction) {
  fprintf(stream, "%c%s\n", instruction->instruction_bit,
          instruction->binary_value);
}

/* Prints C-instrution in binary form to file */
void fprint_c_instruction(FILE* stream,
                          const struct CInstruction* instruction) {
  fprintf(stream, "%c%s%s%s%s\n", instruction->instruction_bit,
          instruction->fixed.binary, instruction->comp.binary,
          instruction->dest.binary, instruction->jump.binary);
}
