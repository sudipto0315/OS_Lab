#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int original_fd = open("example.txt", O_RDONLY);

    if (original_fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate the file descriptor
    int duplicated_fd = dup2(original_fd, 100); // 100 is the new file descriptor that we are assigning.

    if (duplicated_fd == -1) {
        perror("Error duplicating file descriptor");
        close(original_fd);
        return 1;
    }

    // Now 'original_fd' and 'new_fd' refer to the same file.

    // The duplicated_fd is a duplicate of fileDescriptor
    fprintf(stdout, "original_fd: %d\n", original_fd);
    fprintf(stdout, "duplicated_fd: %d\n", duplicated_fd);

    // Close the original file descriptor
    close(original_fd);

    // Use the duplicated file descriptor as needed

    // Close the duplicated file descriptor when done
    close(duplicated_fd);

    return 0;
}