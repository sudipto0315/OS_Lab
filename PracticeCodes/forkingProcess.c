#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
int main(){
    pid_t pid;
    pid=fork();
    if(pid<0){ //error occured
        fprintf(stderr,"Fork Failed");
        return 1;
    }else if(pid==0){
        execlp("/bin/ls","ls",NULL); // what is execlp? // explain in comments 
        // execlp() is a system call that is used to execute a file. It is a varient of exec() system call.
        // The difference between exec() and execlp() is that, execlp() accepts the file name as an argument and searches for the file in the PATH environment variable.
        // If the file is found, it is executed as a new process using the parameters passed to execlp() as arguments.
        // If the file is not found, execlp() returns -1.
    }else{ // parent process
        // parent will wait for the child to complete
        wait(NULL);
        printf("Child Complete");
    }
    return 0;
}