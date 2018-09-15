#include "errors.h"
#include "turing.h"

void error(int errcode)
{
    // associated with every error code there is an error message
    switch (errcode) {
    case INVALID_OP:
        fprintf(stderr, "%s*** Invalid operation ***%s\n",
                RED, NORMAL);
        break;

    case ZERO_DIVISION:
        fprintf(stderr, "%s*** Attempt to divide by zero ***\n%s",
                RED, NORMAL);
        break;

    case OVERFLOW:
        fprintf(stderr, "%s*** Overflow: the number is too big ***\n%s",
                RED, NORMAL);
        break;

    case INVALID_INPUT:
        fprintf(stderr, "%s*** Invalid input ***\n%s",
                RED, NORMAL);
        break;

    case SYNTAX_ERROR:
        fprintf(stderr, "%s*** Syntax error ***\n%s",
                RED, NORMAL);
        break;

    case UNKNOWN_ERROR:
        fprintf(stderr, "%s*** Unknown error ***\n%s",
                RED, NORMAL);
        break;
    }
}
