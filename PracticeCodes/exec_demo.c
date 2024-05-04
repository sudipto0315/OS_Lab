#include<stdio.h>
#include<unistd.h>
int main(){
    printf("I am in exec.c\n");
    char *args[] = {"./hello", NULL};
    execv(args[0], args); 
    // execlp("/home/sudipto/OS_Lab/PracticeCodes/hello","./hello",NULL);
    
    //hints
    // execl() stands for execute list.
    // execlp() stands for execute list of parameters.
    // execle() stands for execute list of parameters with environment.
    // execv() stands for execute vector.
    // execvp() stands for execute vector of parameters.
    // execvpe() stands for execute vector of parameters with environment.
    // printf("coming back to exec.c\n"); // This line will not be executed as 
    // execv() replaces the current process with the new process that is in the 
    // args array(./hello).
    return 0;
}