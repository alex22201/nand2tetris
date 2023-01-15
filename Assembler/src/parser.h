/* 
  Implements parsing assembler instructions and separating
  the required block from the instruction.
*/
#ifndef HACKASSEMBLER__PARSER_H_
#define HACKASSEMBLER__PARSER_H_

/* 
  Parses full assembler C-instruction and extracts Destination part from it.
  Return Destination instruction part.
*/
char* divide_c_instruction_dest(const char* asm_instruction);

/* 
  Parses full assembler C-instruction and extracts Jump part from it.
  Return Jump instruction part.
*/
char* divide_c_instruction_jump(const char* asm_instruction);

/* 
  Parses full assembler C-instruction and extracts Computation part from it.
  Return Computation instruction part.
*/
char* divide_c_instruction_comp(const char* asm_instruction);

#endif  // HACKASSEMBLER__PARSER_H_
