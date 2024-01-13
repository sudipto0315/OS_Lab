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
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        exit(1);
    }

    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "w");

    if (!file1 || !file2) {
        perror("Error opening files");
        exit(1);
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        exit(1);
    }

    pid_t count_pid, convert_pid;

    if ((count_pid = fork()) == 0) {
        // Child 1 (count)
        close(pipe_fd[1]);  // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);  // Close read end of the pipe
        count();
        exit(0);
    } else if ((convert_pid = fork()) == 0) {
        // Child 2 (convert)
        close(pipe_fd[0]);  // Close read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);  // Close write end of the pipe
        convert();
        exit(0);
    } else {
        // Parent
        close(pipe_fd[0]);  // Close both ends of the pipe
        close(pipe_fd[1]);

        int status;
        waitpid(count_pid, &status, 0);
        waitpid(convert_pid, &status, 0);

        fclose(file1);
        fclose(file2);
        exit(0);
    }

    return 0;
}
