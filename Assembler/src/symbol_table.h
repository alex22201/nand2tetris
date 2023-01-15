#include "hash_table.h"

#ifndef HACKASSEMBLER__SYMBOL_TABLE_H_
#define HACKASSEMBLER__SYMBOL_TABLE_H_

/* 
  Creates symbol table based on hash table.
  Return NULL if could not allocate memory.
*/
ht_hash_table_t* create_symbol_table(size_t line_count);

#endif  // HACKASSEMBLER__SYMBOL_TABLE_H_
