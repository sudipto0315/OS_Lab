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
    ssize_t bytesRead = read(file_descriptor, buffer, sizeof(buffer));

    // Do something with the read data

    close(file_descriptor);

    return 0;
}
