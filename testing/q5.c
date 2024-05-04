#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

void count() {
    int ch;
    int nonAlphabeticCount = 0;

    while ((ch = getchar()) != EOF) {
        if (!isalpha(ch)) {
            nonAlphabeticCount++;
        }
        putchar(ch);
    }

    fprintf(stdout, "Count of non-alphabetic characters: %d\n", nonAlphabeticCount); 
    fprintf(stderr, "Count of non-alphabetic characters: %d\n", nonAlphabeticCount); 
}

void convert() {
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
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        exit(1);
    }

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    if (!input_file || !output_file) {
        perror("Error opening files");
        exit(1);
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        exit(1);
    }
    
    dup2(fileno(input_file), STDIN_FILENO);

    pid_t count_pid, convert_pid;
    if ((count_pid = fork()) == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        dup2(fileno(output_file), STDOUT_FILENO);
        count();
        exit(0);
    } else if ((convert_pid = fork()) == 0) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        dup2(fileno(output_file), STDOUT_FILENO);  
        close(pipe_fd[0]);
        convert();
        exit(0);
    } else {
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        int status;
        waitpid(count_pid, &status, 0);
        waitpid(convert_pid, &status, 0);

        fclose(input_file);
        fclose(output_file);
        exit(0);
    }

    return 0;
}