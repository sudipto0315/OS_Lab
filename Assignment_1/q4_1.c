#include <fcntl.h>
#include <stdio.h>

int main() {
    int file_descriptor = open("example.txt", O_CREAT | O_WRONLY, 0644);

    if (file_descriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    // Do something with the file

    close(file_descriptor);
    return 0;
}
