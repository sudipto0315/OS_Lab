#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int original_fd = open("example.txt", O_RDONLY);

    if (original_fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int new_fd = open("duplicate.txt", O_CREAT | O_WRONLY, 0644);

    if (new_fd == -1) {
        perror("Error opening new file");
        close(original_fd);
        return 1;
    }

    // Duplicate 'original_fd' to 'new_fd'
    dup2(original_fd, new_fd);

    // Now 'original_fd' and 'new_fd' refer to the same file.

    close(original_fd);
    close(new_fd);

    return 0;
}
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
