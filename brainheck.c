#include <stdio.h>
#include <stdlib.h>

static void brainheck(char *program) {
    char memory[30000] = {0};
    char *dp = memory;
    char *ip = program;
    while (*ip != '\0') {
        switch (*ip++) {
            case '>': ++dp;                break;
            case '<': --dp;                break;
            case '+': ++*dp;               break;
            case '-': --*dp;               break;
            case '.': putchar(*dp);        break;
            case ',': *dp = getchar();     break;
            case '[': {
                if (*dp != 0) {
                    break;
                }
                int depth = 1;
                while (depth != 0) {
                    switch (*ip++) {
                        case '[': ++depth; break;
                        case ']': --depth; break;
                    }
                }
                break;
            }
            case ']': {
                if (*dp == 0) {
                    break;
                }
                ip--; /* move back to the ']' */
                int depth = 1;
                while (depth != 0) {
                    switch (*--ip) {
                        case '[': --depth; break;
                        case ']': ++depth; break;
                    }
                }
                ip++; /* move right past '[' */
                break;
            }
        }
    }
}

static void run_file(char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (f == NULL) {
        fprintf(stderr, "Could not open '%s'\n", fileName);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    rewind(f);

    char *contents = malloc(fsize + 1);
    if (contents == NULL) {
        fprintf(stderr, "Could not allocate storage for the program");
        exit(1);
    }

    size_t bytes_read = fread(contents, sizeof(char), fsize, f);
    if (bytes_read != fsize) {
        fprintf(stderr, "Could not read file '%s'\n", fileName);
        exit(1);
    }
    fclose(f);

    contents[fsize] = '\0';
    brainheck(contents);
    free(contents);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file.bf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    run_file(argv[1]);
    return EXIT_SUCCESS;
}
