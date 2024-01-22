#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int file_descriptor = open("example2.txt", O_CREAT | O_WRONLY, 0644);

    if (file_descriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    char data[] = "Hello, World! this text was written using write() from q4_7.c\n";
    ssize_t bytesWritten = write(file_descriptor, data, sizeof(data) - 1);

    // Check for errors and do something with the written data

    close(file_descriptor);

    return 0;
}
