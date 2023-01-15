#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "assembler.h"
#include "instructions.h"

static FILE* input_file = NULL;
static FILE* output_file = NULL;

/* Parses command line args */
static int process_args(int argc, char* argv[argc + 1]) {
  int opt;

  while ((opt = getopt(argc, argv, "i:o:")) != -1) {
    switch (opt) {
      case 'o':
        output_file = fopen(optarg, "w");
        break;
      case 'i':
        input_file = fopen(optarg, "r");
        break;
      default:
        fprintf(stderr, "Usage: %s [-i] [file...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  if (!input_file) {
    fprintf(stderr, "Incorrect input file!\n");
    exit(EXIT_FAILURE);
  }
  if (!output_file) {
    output_file = fopen("result.hack", "w");
  }

  return optind;
}

int main(int argc, char* argv[argc + 1]) {
  process_args(argc, argv);

  assemble(input_file, output_file);

  fclose(input_file);
  fclose(output_file);
  return EXIT_SUCCESS;
}
