#include "turing.h"

int input(int *memory, int size, reg_t *r)
{
    int tmp;

    
    printf("\n");
    while (r->ic < size) {  // while there is still free memory
        printf("%s%02d%s > ", GREEN, r->ic, NORMAL); // print current instruction counter

        if(!scanf("%d", &r->ir)) {
            error(INVALID_INPUT);
            return (EXIT_CODE);
        }

        // if the sentinel value is typed, stop accepting inputs
        if (r->ir == SENT) {
            break;
        }

        // this gives control to the main function, which will quit the program
        if (r->ir == EXIT_CODE) {
            return (EXIT_CODE);
        }

        // check the given word, give error in case
        r->opcode = (r->ir) / 100;
        r->operand = (r->ir) % 100;

        if (chkopcode(r->opcode) && chkoperand(r->operand, MAXMEM)) {

            if (r->opcode == READ) {
                printf("WRITE ON LOCATION %d: ", r->operand);
                if (!scanf("%d", &tmp)) {
                    error(INVALID_INPUT);
                    return (EXIT_CODE);
                }

                if (!chknum(tmp)) {
                    error(OVERFLOW);
                    continue;
                } else {
                    memory[r->operand] = tmp;
                }
            }

            // if everything's good, write the word on memory
            memory[r->ic] = r->ir;
            r->ic++;

        } else {
            error(INVALID_OP);
            continue;
        }

    }
}

int parser(char *token)
{
    // returns the op code for each read string from a file
    if (!strcmp(token, "VAR"))
        return READ;
    else if (!strcmp(token, "PRINT"))
        return WRITE;
    else if (!strcmp(token, "LOAD"))
	    return LOAD;
    else if (!strcmp(token, "STORE"))
        return STORE;
    else if (!strcmp(token, "ADD"))
        return ADD;
    else if (!strcmp(token, "SUB"))
        return SUB;
    else if (!strcmp(token, "MUL"))
        return MUL;
    else if (!strcmp(token, "DIV"))
        return DIV;
    else if (!strcmp(token, "JUMP"))
        return BRANCH;
    else if (!strcmp(token, "JUMPNEG"))
        return BRANCHNEG;
    else if (!strcmp(token, "JUMPZERO"))
        return BRANCHZERO;
    else if (!strcmp(token, "HALT"))
        return HALT;
    else
        return SYNTAX_ERROR;
}

int file_input(int *memory, int size, char *file_name, reg_t *r)
{
	FILE *fp;
	char f_opcode[10]; // where 10 is the max size of an operator (check parser() to see why)
    int tmp;

	fp = fopen(file_name, "r");

	if (fp == NULL) {
		fprintf(stderr, "[%s*%s] Can't open file.\n",
                RED, NORMAL);
		return (EXIT_CODE);
	}

	while (!feof(fp) && r->ic < size) {

        // fscanf must read at least one field (like when the command is HALT)
		if(fscanf(fp, "%s %d", f_opcode, &r->operand) < 1) {
            fprintf(stderr, "[%s*%s] Error reading from file.\n",
                RED, NORMAL);
            return (EXIT_CODE);
        }

        // pass the string to the parser which returns the op code
		r->opcode = parser(f_opcode);

        // if the string is unknown give a syntax error
        if (r->opcode == SYNTAX_ERROR) {
            error(SYNTAX_ERROR);
            printf("(line %d)\n", (r->ic + 1));
            return (EXIT_CODE);
        }

        // if the operand is not a valid memory cell
        if (!chkoperand(r->operand, MAXMEM)) {
            error(INVALID_OP);
            return (EXIT_CODE);
        }

        r->ir = ((r->opcode) * 100) + r->operand;

		if (r->opcode == READ) {
			if(fscanf(fp, "%d", &tmp) < 1) {
                fprintf(stderr, "[%s*%s] Error reading from file.\n",
                    RED, NORMAL);
            }

            if (!chknum(tmp)) {
                error(OVERFLOW);
                printf("(line %d)\n", (r->ic + 1));
                return (EXIT_CODE);
            } else {
                memory[r->operand] = tmp;
            }

		}

        // save the instruction to a memory cell if each check
        // doesn't give any errors
		memory[r->ic] = r->ir;
		r->ic++;
	}

    fclose(fp);
}
