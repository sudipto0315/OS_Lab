// to compile this file use:
// gcc q3.c
// ./a.out <input.txt
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    int ch;

    while ((ch = getchar()) != EOF) {
        // Reverse the case of alphabetic characters
        if (isalpha(ch)) {
            if (islower(ch)) {
                ch = toupper(ch);
            } else {
                ch = tolower(ch);
            }
        }

      
        putchar(ch);
    }

    // Exit with status code 0 when EOF is reached
    exit(0);
}
