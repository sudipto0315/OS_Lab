#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> // used for fork (unix standard)
#include <sys/wait.h> // used for waitpid

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
    // we are printing to stderr because we are redirecting stdout to a file so we can't print to stdout
    // which file are we redirecting stdout to? // we are redirecting stdout to the output file
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

    FILE *input_file = fopen(argv[1], "r"); // why *input_file and not input_file? // because fopen returns a pointer to a FILE struct
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
    
    // Redirect stdin of the parent process to the input file
    dup2(fileno(input_file), STDIN_FILENO);

    pid_t count_pid, convert_pid; // pid_t is a signed integer type which is capable of representing a process ID 
    // what is a process ID? // a process ID is a unique identifier for a process
    // why count_pid and convert_pid? // because we are creating two child processes (count and convert)
    if ((count_pid = fork()) == 0) { // what is fork? // fork() creates a new process by duplicating the calling process
        // 0 means success, -1 means error, and > 0 is the process ID of the child process
        // Child 1 (count)
        close(pipe_fd[0]);  // Close write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO); // what is STDIN_FILENO? // STDIN_FILENO is a macro defined in unistd.h which is the file descriptor for stdin that id 0
                                        // default file descriptors for stdin, stdout, and stderr are 0, 1, and 2 respectively
        close(pipe_fd[1]);  // Close read end of the pipe
        dup2(fileno(output_file), STDOUT_FILENO); // what is STDERR_FILENO? // STDERR_FILENO is a macro defined in unistd.h which is the file descriptor for stderr that id 2
        count(); // what is count? // count is a function that counts the number of non-alphabetic characters in a file
        exit(0);
    } else if ((convert_pid = fork()) == 0) {
        // Child 2 (convert)
        close(pipe_fd[1]);  // Close read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        dup2(fileno(output_file), STDOUT_FILENO);  
        close(pipe_fd[0]);  // Close write end of the pipe
        convert(); // what is convert? // convert is a function that converts all lowercase characters to uppercase and vice versa
        exit(0);
    } else {
        // Parent
        close(pipe_fd[0]);  // Close both ends of the pipe
        close(pipe_fd[1]);

        int status;
        waitpid(count_pid, &status, 0); // what is waitpid? // waitpid() suspends execution of the calling process until a child specified by pid argument has changed state
        // why &status? // because waitpid() returns the process ID of the child whose state has changed, or -1 if an error occurred
        // why 0? // 0 means wait for any child process whose process group ID is equal to that of the calling process
        waitpid(convert_pid, &status, 0);

        fclose(input_file);
        fclose(output_file);
        exit(0);
    }

    return 0;
}
