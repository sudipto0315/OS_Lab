#include <stdio.h>

int main(int argc, char *argv[]) {// why argv has a pointer? why not just char argv[]?
    // argv is a pointer to an array of strings. The array is of type char*[].
    // If we use char argv[], then we are declaring an array of characters, not an array of strings.

    // Skip the first argument, as it is the program name itself
    for (int i = 1; i < argc; ++i) {
        // Check if the argument does not start with a dash
        if (argv[i][0] != '-') {
            // Print the argument followed by a space
            printf("%s ", argv[i]);
        }
    }

     //Print a newline character if there were arguments without a dash
     if (argc > 1) {
         printf("\n");
     }

    return 0;
}
