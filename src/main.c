#include "turing.h"

#ifdef linux
    #define CLEAR_STRING "clear"
#endif

#ifdef _WIN32
    #define CLEAR_STRING "cls"
#endif

// Others
#define BANNER 32

// Versioning
#define MAJOR 2
#define MINOR 0

int welcome(void)
{
    FILE *bannerf;
    char str[BANNER];

    if ((bannerf = fopen("banner", "r")) == NULL) {
        fprintf(stderr, "[%s*%s] Can't open banner file.\n",
                RED, NORMAL);
        return 1;
    }

    system(CLEAR_STRING);

    // read every line from the banner file and print it on screen
    while (fgets(str, sizeof(str), bannerf) != NULL) {
        printf("\t%s%s%s", GREEN, str, NORMAL);
    }

    fclose(bannerf);

    printf("Please enter your program one instruction\n"
        "at a time. Type -99999 to stop entering\n"
        "your program. Type 99999 to exit.\n");

    return 0;
}

void usage(void)
{
    printf("turing v%d.%d\n\n"
        "A simple machine simulator written in C.\n"
        "Developed by %sdrvladbancila%s: "
        "https://github.com/drvladbancila/turing\n\n", 
        MAJOR, MINOR, GREEN, NORMAL);
    
    printf("%sUsage:%s turing <flag> [arguments]\n\n"
        "%sFlags:%s\n"
        "-h, --help\tShow help text and exit\n"
        "-b, --boot\tBoots the machine.\n"
        "-f, --file\tRun a program from the file specified as [argument].\n"
        "-d, --dump\tDumps the memory (in combination with -b and -f).\n\n",
        GREEN, NORMAL, GREEN, NORMAL);
    
    printf("%sExamples:%s\n\tturing -f -d program_file\n"
        "\tturing -b -d\n", GREEN, NORMAL);
}

int main(int argc, char *argv[])
{
    int memory[MAXMEM];
    reg_t registers;
    
    int dump_mode = 0;
    int file_mode = 0;
    int no_file = 0;
    int file_position = 2;
    int exit_condition = 0;
    
    // if not enough arguments are given, print usage
    if (argc < 2) {
        usage();
        return (EXIT_FAILURE);
    }
    
    if (!strcmp(argv[1], "-h") || 
        !strcmp(argv[1], "--help")) {
        usage();
        return (EXIT_SUCCESS);
    }
    
    if (!strcmp(argv[1], "-b") ||
        !strcmp(argv[1], "--boot")) {
        file_mode = 0;
    } else if (!strcmp(argv[1], "-f") ||
        !strcmp(argv[1], "--file")) {
        file_mode = 1;
    } else {
        usage();
        return (EXIT_FAILURE);
    }
    
    if (argc > 2 && (!strcmp(argv[2], "-d") ||
        !strcmp(argv[2], "--dump"))) {
        dump_mode = 1;
        file_position++; // if there is the -d flag, the file name will be the third argument
    }
    
    if (!file_mode) {   // live mode activated
        if (welcome() == 1) {
            return (EXIT_FAILURE);
        }
        
        while (exit_condition != EXIT_CODE) {
            free_memory(memory, MAXMEM, &registers);
            exit_condition = input(memory, MAXMEM, &registers);

            run(memory, MAXMEM, &registers);
            
            if (dump_mode) {
                dump(memory, MAXMEM, &registers);
            }

            if (exit_condition == SENT) {
                continue;
            }
        }
    } else {    // file mode activated
        if (dump_mode && argc != 4) {
            no_file = 1;
        }
        
        if (!dump_mode && argc != 3) {
            no_file = 1;
        }
        
        if (no_file) {
            fprintf(stderr, "[%s*%s] No input file.\n", RED, NORMAL);
            return (EXIT_FAILURE);
        } else {
            free_memory(memory, MAXMEM, &registers);
            exit_condition = file_input(memory, MAXMEM, argv[file_position], &registers); // argv[2] is the file name

            if (exit_condition == EXIT_CODE) {
                return (EXIT_FAILURE);
            } else {
                run(memory, MAXMEM, &registers);
            }
            
            // if the "dump mode" is on, dump the memory at the end
            if (dump_mode) {
                dump(memory, MAXMEM, &registers);
            }
        }
    }
    
    return (EXIT_SUCCESS);
}
