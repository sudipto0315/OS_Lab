#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int file_descriptor = open("example.txt", O_RDONLY);

    if (file_descriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(file_descriptor, buffer, sizeof(buffer)); // read() returns the number of bytes read, or -1 if an error occurred
    fprintf(stdout, "There are %ld bytes in the file\n", bytesRead);
    fprintf(stdout, "Contents of file:\n%s\n", buffer);
    close(file_descriptor);

    return 0;
}
