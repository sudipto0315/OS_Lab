#include <fcntl.h>
#include <stdio.h>

int main() {
    int file_descriptor = creat("example.txt", 0644);

    if (file_descriptor == -1) {
        perror("Error creating file");
        return 1;
    }

    // Do something with the file

    close(file_descriptor);
    return 0;
}
