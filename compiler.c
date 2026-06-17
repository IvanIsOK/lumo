#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 4096

// ================= TOKENS =================

typedef enum {
    T_LET, T_PRINT,
    T_ID, T_NUM,
    T_EQ,
    T_SEMI,
    T_EOF
} TokenType;

typedef struct {
    TokenType type;
    char text[64];
} Token;

Token tokens[MAX];
int pos = 0;
int tcount = 0;

char *src;

// ================= LEXER =================

void add(TokenType t, char *txt) {
    tokens[tcount].type = t;
    if (txt) strcpy(tokens[tcount].text, txt);
    else tokens[tcount].text[0] = 0;
    tcount++;
}

void lex(char *s) {
    src = s;

    while (*src) {
        if (isspace(*src)) { src++; continue; }

        if (strncmp(src, "let", 3) == 0) {
            add(T_LET, "let"); src += 3; continue;
        }

        if (strncmp(src, "print", 5) == 0) {
            add(T_PRINT, "print"); src += 5; continue;
        }

        if (*src == '=') { add(T_EQ, "="); src++; continue; }
        if (*src == ';') { add(T_SEMI, ";"); src++; continue; }

        if (isdigit(*src)) {
            char b[64]; int i = 0;
            while (isdigit(*src)) b[i++] = *src++;
            b[i] = 0;
            add(T_NUM, b);
            continue;
        }

        if (isalpha(*src)) {
            char b[64]; int i = 0;
            while (isalnum(*src)) b[i++] = *src++;
            b[i] = 0;
            add(T_ID, b);
            continue;
        }

        printf("Lex error: %c\n", *src);
        exit(1);
    }

    add(T_EOF, "");
}

// ================= CODEGEN (ASM) =================

FILE *out;

void emit(const char *s) {
    fprintf(out, "%s\n", s);
}

// single variable model (x only for v2)
void compile() {
    emit("section .bss");
    emit("x resq 1");

    emit("section .text");
    emit("global _start");

    emit("_start:");

    while (tokens[pos].type != T_EOF) {

        // let x = num;
        if (tokens[pos].type == T_LET) {
            pos++; // let
            pos++; // id (assume x)
            pos++; // =

            int value = atoi(tokens[pos].text);
            pos++; // num

            char buf[128];
            sprintf(buf, "mov qword [x], %d", value);
            emit(buf);

            pos++; // ;
        }

        // print x;
        else if (tokens[pos].type == T_PRINT) {
            pos++;
            pos++; // id
            pos++; // ;

            emit("; print x (syscall raw placeholder)");
            emit("mov rax, 1");
            emit("mov rdi, 1");
            emit("mov rsi, x");
            emit("mov rdx, 8");
            emit("syscall");
        }
    }

    emit("mov rax, 60");
    emit("mov rdi, 0");
    emit("syscall");
}

// ================= MAIN =================

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: lumo file.lumo\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char buf[10000];
    fread(buf, 1, sizeof(buf), f);
    fclose(f);

    lex(buf);

    out = fopen("out.asm", "w");
    compile();
    fclose(out);

    system("nasm -f elf64 out.asm -o out.o");
    system("ld out.o -o program");

    printf("Built program\n");
    return 0;
}
