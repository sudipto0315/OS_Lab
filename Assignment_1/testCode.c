#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(int argc, char const *argv[])
{
    int fd1 = open("example.txt", O_RDONLY);
    if(fd1 == -1){
        perror("Error opening file");
        return 1;
    }
    char buffer[100];
    ssize_t read_bytes=read(fd1,buffer,sizeof(buffer));
    fprintf(stdout,"%s\n",buffer);
    return 0;
}
