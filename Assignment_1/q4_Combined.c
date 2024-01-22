#include <fcntl.h>
#include <unistd.h>

int main() {
    // open()
    int fd1 = open("test.txt", O_WRONLY | O_CREAT, 0644); // O_WRONLY means write only, O_CREAT means create the file if it doesn't exist, 0644 is the permission
    write(fd1, "Hello from open()!\n", 19);

    // creat()
    int fd2 = creat("newfile.txt", 0644);
    write(fd2, "Hello from creat()!\n", 20);

    // dup()
    int fd3 = dup(fd1); // fd3 is a copy of fd1
    write(fd3, "Hello from dup()!\n", 18);

    // dup2()
    dup2(fd2, fd1); // fd1 is a copy of fd2
    write(fd1, "Hello from dup2()!\n", 19);// 19 is the number of bytes to write

    // pipe()
    int fd[2];
    pipe(fd);
    write(fd[1], "Hello from pipe()!\n", 19);
    char buffer[20];
    read(fd[0], buffer, 19);
    buffer[19] = '\0';
    write(fd1, buffer, 20);
    // close all file descriptors
    close(fd1);
    close(fd2);
    close(fd3);
    close(fd[0]);
    close(fd[1]);

    return 0;
}