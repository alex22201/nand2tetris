#include "symbol_table.h"

#include "hash_table.h"

#define FIXED_INSTRUCTION_COUNT 23

/* Init symbol table by predefined values */
static void init_symbol_table(ht_hash_table_t* symbol_table) {
  // Registers
  ht_insert(symbol_table, "R0", 0);
  ht_insert(symbol_table, "R1", 1);
  ht_insert(symbol_table, "R2", 2);
  ht_insert(symbol_table, "R3", 3);
  ht_insert(symbol_table, "R4", 4);
  ht_insert(symbol_table, "R5", 5);
  ht_insert(symbol_table, "R6", 6);
  ht_insert(symbol_table, "R7", 7);
  ht_insert(symbol_table, "R8", 8);
  ht_insert(symbol_table, "R9", 9);
  ht_insert(symbol_table, "R10", 10);
  ht_insert(symbol_table, "R11", 11);
  ht_insert(symbol_table, "R12", 12);
  ht_insert(symbol_table, "R13", 13);
  ht_insert(symbol_table, "R14", 14);
  ht_insert(symbol_table, "R15", 15);

  // I/O
  ht_insert(symbol_table, "SCREEN", 16384);
  ht_insert(symbol_table, "KBD", 24576);

  // Other symbols
  ht_insert(symbol_table, "SP", 0);
  ht_insert(symbol_table, "LCL", 1);
  ht_insert(symbol_table, "ARG", 2);
  ht_insert(symbol_table, "THIS", 3);
  ht_insert(symbol_table, "THAT", 4);
}

/* 
  Creates symbol table based on hash table.
  Return NULL if could not allocate memory.
*/
ht_hash_table_t* create_symbol_table(size_t line_count) {
  size_t capacity = FIXED_INSTRUCTION_COUNT + line_count;
  ht_hash_table_t* symbol_table = ht_create_sized(capacity);
  if (!symbol_table) return NULL;
  init_symbol_table(symbol_table);

  return symbol_table;
}
