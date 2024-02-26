#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main() {
    int ch;
    
    while ((ch = getchar()) != EOF) {
        if (isalpha(ch)) {
            if (islower(ch)) {
                putchar(toupper(ch));
            } else {
                putchar(tolower(ch));
            }
        } else {
            putchar(ch);
        }
    }
    return 0;
}