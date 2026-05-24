#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *input;

void skip_spaces() {
    while (*input == ' ') {
        input++;
    }
}

int parse_expr();

int parse_number() {
    skip_spaces();

    int num = 0;

    while (isdigit(*input)) {
        num = num * 10 + (*input - '0');
        input++;
    }

    return num;
}

int parse_factor() {
    skip_spaces();

    if (*input == '(') {
        input++;
        int value = parse_expr();

        skip_spaces();

        if (*input == ')') {
            input++;
        }

        return value;
    }

    return parse_number();
}

int parse_term() {
    int value = parse_factor();

    while (1) {
        skip_spaces();

        if (*input == '*') {
            input++;
            value *= parse_factor();
        } else {
            break;
        }
    }

    return value;
}

int parse_expr() {
    int value = parse_term();

    while (1) {
        skip_spaces();

        if (*input == '+') {
            input++;
            value += parse_term();
        }
        else if (*input == '-') {
            input++;
            value -= parse_term();
        }
        else {
            break;
        }
    }

    return value;
}

void generate_asm(int result) {
    FILE *f = fopen("out.s", "w");

    fprintf(f,
        ".global _start\n"
        ".section .text\n"
        "_start:\n"
        "    mov $60, %%rax\n"
        "    mov $%d, %%rdi\n"
        "    syscall\n",
        result
    );

    fclose(f);
}

int main() {
    char buffer[256];

    printf("Enter expression: ");
    fgets(buffer, sizeof(buffer), stdin);

    input = buffer;

    int result = parse_expr();

    printf("Result = %d\n", result);

    generate_asm(result);

    system("gcc -nostdlib out.s -o out");

    printf("Assembly generated in out.s\n");
    printf("Executable generated: out\n");

    return 0;
}
