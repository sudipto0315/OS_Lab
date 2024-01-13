// to compile this file use:
// gcc q2.c
// ./a.out <input.txt
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    int ch;
    int nonAlphabeticCount = 0;

    while ((ch = getchar()) != EOF) {
        if (!isalpha(ch) && ch != '\n') {
            nonAlphabeticCount++;
        }

        putchar(ch);
    }

    fprintf(stdout, "Non-alphabetic count: %d\n", nonAlphabeticCount);

    exit(0);
}
