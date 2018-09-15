#include "checks.h"
#include "turing.h"

int chkopcode(int opcode)
{
    int valid = 1;

    switch (opcode) {
    case READ:
    case WRITE:
    case LOAD:
    case STORE:
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case BRANCH:
    case BRANCHNEG:
    case BRANCHZERO:
    case HALT:
    case 0:
        break;
    default:
        valid = 0;
    }

    return valid;
}

int chkoperand(int operand, int memory_size)
{
	int valid = 1;

    // check if the memory cell actually exists
	if (operand < 0 || operand >= memory_size)
		valid = 0;

	return valid;
}

int chknum(int num)
{
    int valid = 1;

    if (num < -9999 || num > 9999)
        valid = 0;

    return valid;
}
