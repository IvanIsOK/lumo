#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SRC 100000
#define MAX_FILE 512

// ===== read file =====
char* read_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Error: cannot open %s\n", path);
        exit(1);
    }

    char *buf = malloc(MAX_SRC);
    size_t len = fread(buf, 1, MAX_SRC - 1, f);
    buf[len] = 0;

    fclose(f);
    return buf;
}

// ===== handle includes =====
void append_file(char *out, const char *file) {
    char *content = read_file(file);
    strcat(out, content);
    free(content);
}

// ===== preprocess (#include) =====
void preprocess(char *input, char *output) {
    char line[1024];

    char *p = input;
    while (*p) {
        int i = 0;

        while (*p && *p != '\n') {
            line[i++] = *p++;
        }
        line[i] = 0;
        if (*p == '\n') p++;

        // handle include
        if (strncmp(line, "#include", 8) == 0) {
            char filename[MAX_FILE];
            sscanf(line, "#include \"%[^\"]\"", filename);
            append_file(output, filename);
        } else {
            strcat(output, line);
            strcat(output, "\n");
        }
    }
}

// ===== VERY simple backend (placeholder for real compiler pipeline) =====
void compile_to_c(const char *src, FILE *out) {
    fprintf(out, "#include <stdio.h>\n\n");
    fprintf(out, "int main() {\n");

    // NOTE:
    // This is intentionally minimal.
    // Real parser/AST will replace this later.

    char buf[1024];
    const char *p = src;

    while (*p) {
        if (sscanf(p, "%1023[^\n]\n", buf) == 1) {
            p += strlen(buf) + 1;

            // skip includes (already processed)
            if (strncmp(buf, "#include", 8) == 0)
                continue;

            // naive passthrough (temporary stage)
            fprintf(out, "    %s\n", buf);
        } else break;
    }

    fprintf(out, "return 0;\n");
    fprintf(out, "}\n");
}

// ===== MAIN =====
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: lumo main.lumo\n");
        return 1;
    }

    char combined[MAX_SRC] = {0};

    char *src = read_file(argv[1]);

    preprocess(src, combined);

    FILE *out = fopen("out.c", "w");
    if (!out) {
        printf("Error writing output\n");
        return 1;
    }

    compile_to_c(combined, out);

    fclose(out);
    free(src);

    system("gcc out.c -o program");

    printf("Built: program\n");
    return 0;
}
