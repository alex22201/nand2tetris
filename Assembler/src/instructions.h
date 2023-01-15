/* Creating instruction structures from parsed assembler instruciton strings */
#include <stdbool.h>
#include <stdio.h>

#include "hash_table.h"

#ifndef HACKASSEMBLER__INSTRUCTIONS_H_
#define HACKASSEMBLER__INSTRUCTIONS_H_

/******* Instruction structures *******/

/* Fixed part of C-instruction */
struct CInstructionFixed {
  // first 2 fixed bits (==1) + '\0'
  char binary[3];
};

/* Destination part of C-instruction */
struct CInstructionDest {
  // d1 d2 d3 bits + '\0'
  bool ram;
  bool a_register;
  bool d_register;
  char binary[4];
};

/* Enumeration of allowed operations in Computation part of C-instruction */
enum CompOperation {
  Zero,
  One,
  MinusOne,
  DRegister,
  ARegister,
  NotDRegister,
  NotARegister,
  MinusDRegister,
  MinusARegister,
  DRegisterPlusOne,
  ARegisterPlusOne,
  DRegisterMinusOne,
  ARegisterMinusOne,
  DRegisterPlusARegister,
  DRegisterMinusARegister,
  ARegisterMinusDRegister,
  DRegisterAndARegister,
  DRegisterOrARegister,
  RAM,
  NotRAM,
  MinusRAM,
  RAMPlusOne,
  RAMMinusOne,
  DRegisterPlusRAM,
  DRegisterMinusRAM,
  RAMMinusDRegister,
  DRegisterAndRAM,
  DRegisterOrRAM,
};

/* Computation part of C-instruction */
struct CInstructionComp {
  // a c1 c2 c3 c4 c5 c6 bits + '\0'
  enum CompOperation operation;
  char binary[8];
};

/* Jump part of C-instruction */
struct CInstructionJump {
  // j1 j2 j3 bits + '\0'
  bool greater;
  bool equal;
  bool lower;
  char binary[4];
};

/* Full C-instruction structure */
struct CInstruction {
  // dest = comp ; jump
  char instruction_bit;
  struct CInstructionFixed fixed;
  struct CInstructionComp comp;
  struct CInstructionDest dest;
  struct CInstructionJump jump;
};

/* Full A-instruction structure */
struct AInstruction {
  char instruction_bit;
  int value;              // 10-base value
  char binary_value[16];  // 15 bits + '\0'
};

/******* Operations with instructions *******/

/* Creates A-instruction from integer value */
struct AInstruction create_a_instruction(ht_value_t value);

/* Creates C-instruction from prepared parts (Comp, Dest, Jump) */
struct CInstruction create_c_instruction(struct CInstructionComp comp,
                                         struct CInstructionDest dest,
                                         struct CInstructionJump jump);

/* Creates Computation part of C-instruction */
struct CInstructionComp create_c_instruction_comp(
    const char* asm_comp_instruction);

/* Creates Jump part of C-instruction */
struct CInstructionJump create_c_instruction_jump(
    const char* asm_jump_instruction);

/* Creates Destination part of C-instruction */
struct CInstructionDest create_c_instruction_dest(
    const char* asm_dest_instruction);

/* Prints A-instrution in binary form to file */
void fprint_a_instruction(FILE* stream, const struct AInstruction* instruction);

/* Prints C-instrution in binary form to file */
void fprint_c_instruction(FILE* stream, const struct CInstruction* instruction);
#endif  // HACKASSEMBLER__INSTRUCTIONS_H_
