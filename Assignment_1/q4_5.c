#include <unistd.h>
#include <stdio.h>

int main() {
    int pipe_fd[2]; // what is pipe? https://www.geeksforgeeks.org/pipe-system-call/ 
    // pipe_fd[0] is the read end of the pipe, and pipe_fd[1] is the write end of the pipe.
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        return 1;
    }
    
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
