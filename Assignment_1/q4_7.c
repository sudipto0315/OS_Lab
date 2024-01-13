#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int file_descriptor = open("example.txt", O_CREAT | O_WRONLY, 0644);

    if (file_descriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    char data[] = "Hello, World!";
    ssize_t bytesWritten = write(file_descriptor, data, sizeof(data) - 1);

    // Check for errors and do something with the written data

    close(file_descriptor);

    return 0;
}
