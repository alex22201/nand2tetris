#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instructions.h"
#include "symbol_table.h"

#ifndef HACKASSEMBLER__ASSEMBLER_H_
#define HACKASSEMBLER__ASSEMBLER_H_

/* Translates assembler instructions from input_f to binary code in output_f */
void assemble(FILE* input_f, FILE* output_f);

#endif  // HACKASSEMBLER__ASSEMBLER_H_

