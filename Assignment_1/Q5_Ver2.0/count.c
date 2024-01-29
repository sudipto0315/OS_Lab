#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main() {
    int ch;
    int nonAlphabeticCount = 0;

    while ((ch = getchar()) != EOF) {
        if (!isalpha(ch)) {
            nonAlphabeticCount++;
            printf("%c", ch);
        }
    }

    fprintf(stdout, "Count of non-alphabetic characters: %d\n", nonAlphabeticCount); 
    // we are printing to stderr because we are redirecting stdout to a file so we can't print to stdout
    // which file are we redirecting stdout to? // we are redirecting stdout to the output file
    return 0;
}