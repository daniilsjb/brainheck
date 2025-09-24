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
                if (*dp != 0) break;
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
                if (*dp == 0) break;
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

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file.bf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        fprintf(stderr, "Could not open '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    rewind(file);

    char *program = malloc(fsize + 1);
    fread(program, sizeof(char), fsize, file);
    program[fsize] = '\0';
    fclose(file);

    brainheck(program);
    free(program);
    return EXIT_SUCCESS;
}
