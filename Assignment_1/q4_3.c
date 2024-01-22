#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int original_fd = open("example.txt", O_RDONLY);
    // fd means file descriptor. It is an integer that uniquely identifies an open file in a process.
    if (original_fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int duplicated_fd = dup(original_fd);
    fprintf(stdout, "original_fd: %d\n", original_fd);
    fprintf(stdout, "duplicated_fd: %d\n", duplicated_fd);
    // Now 'original_fd' and 'duplicated_fd' refer to the same file.

    close(original_fd);
    close(duplicated_fd);

    return 0;
}
