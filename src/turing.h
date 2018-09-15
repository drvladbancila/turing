// Registers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"
#include "colors.h"
#include "errors.h"
#include "checks.h"

// Hardware limits
#define MAXMEM 100
#define WORD 4

typedef struct {
    int acc;    // Accumulator
    int ic;     // Instruction Counter
    int ir;     // Instruction Register
    int opcode;
    int operand;
} reg_t;

int input(int *memory, int size, reg_t *r);
int file_input(int *memory, int size, char *file_name, reg_t *r);
int parser(char *token);

void run(int *memory, int size, reg_t *r);
void free_memory(int *, int, reg_t *);
void dump(int *, int, reg_t *);
