#include "turing.h"

void run(int *memory, int size, reg_t *r)
{
    int halt = 0;
    int tmp;

    printf("\n%s*** Program execution begins ***%s\n\n",
            BLU, NORMAL);

    for (r->ic = 0; r->ic < MAXMEM && !halt; r->ic++) {
        r->ir = memory[r->ic];

        r->opcode = r->ir / 100;
        r->operand = r->ir % 100;

        switch (r->opcode) {
        case READ:
            break;

        case WRITE:
            printf("DATA ON LOCATION %d: %d\n",
                r->operand, memory[r->operand]);
            break;

        case LOAD:
            r->acc = memory[r->operand];
            break;

        case STORE:
            memory[r->operand] = r->acc;
            break;

        case ADD:
            tmp = r->acc + memory[r->operand];
            if (!chknum(tmp)) {
                error(OVERFLOW);
                halt = 1;
            } else {
                r->acc = tmp;
            }
            break;

        case SUB:
            tmp = r->acc - memory[r->operand];
            if (!chknum(tmp)) {
                error(OVERFLOW);
                halt = 1;
            } else {
                r->acc = tmp;
            }
            break;

        case MUL:
            tmp = r->acc * memory[r->operand];
            if (!chknum(tmp)) {
                error(OVERFLOW);
                halt = 1;
            } else {
                r->acc = tmp;
            }
            break;

        case DIV:
            if (!memory[r->operand]) {
                error(ZERO_DIVISION);   // if someone's attempting to divide by zero
                halt = 1;               // halt the execution
            } else {
               tmp = r->acc / memory[r->operand];
                if (!chknum(tmp)) {
                    error(OVERFLOW);
                    halt = 1;
                } else {
                    r->acc = tmp;
                }
            }
            break;

        // in the following jump instructions there is a "-1" because
        // at the end of the loop, r->ic gets increased by one
        case BRANCH:
            r->ic = r->operand - 1;
            break;

        case BRANCHNEG:
            if ((r->acc) < 0)
                r->ic = r->operand - 1;
            break;

        case BRANCHZERO:
            if (!(r->acc))
                r->ic = r->operand - 1;
            break;

        case HALT:
            halt = 1;
            break;
        }
    }

    printf("\n%s*** Program execution terminated ***%s\n\n",
            BLU, NORMAL);
}

void free_memory(int *memory, int size, reg_t *r)
{
    int i;

    // reset all the registers
    r->acc = 0;
    r->ic = 0;
    r->ir = 0;
    r->operand = 0;
    r->opcode = 0;

    for (i = 0; i < size; i++) {
        memory[i] = 0; // write zeros on every cell
    }
}

void dump(int *memory, int size, reg_t *r)
{
    int i;

    printf("%sREGISTERS: %s\n\n", GREEN, NORMAL);
    printf("ACC: \t\t%+05d\n"
           "IC: \t\t%02d\n"
           "IR: \t\t%+05d\n"
           "OP CODE: \t%02d\n"
           "OPERAND: \t%02d\n\n",
           r->acc, r->ic,
           r->ir, r->opcode,
           r->operand);

    printf("%sMEMORY DUMP: %s\n\n", GREEN, NORMAL);

    printf("%3c", ' ');
    for (i = 0; i < 10; i++) {
        printf("%s% 6d%s", YELLOW, i, NORMAL);  // print the 'coordinates'
    }
    printf("\n");

    for (i = 1; i <= size; i++) {
        if (i == 1) {
            printf("%s% 2d  %s", YELLOW, i, NORMAL);
        }

        if (memory[i - 1] != 0) {
            printf("%s%+05d %s", GREEN, memory[i - 1], NORMAL);
        } else {
            printf("%+05d ", memory[i - 1]);
        }

        if (i % 10 == 0 && i != MAXMEM) {
            printf("\n");
            printf("%s% 2d %s", YELLOW, i, NORMAL);
        }
    }
    printf("\n");
}
