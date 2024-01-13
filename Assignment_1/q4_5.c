#include <unistd.h>
#include <stdio.h>

int main() {
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        return 1;
    }

    // Now pipe_fd[0] is the read end, and pipe_fd[1] is the write end of the pipe.

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
