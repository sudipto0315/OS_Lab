#include <stdio.h>

int main(int argc, char *argv[]) {
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
