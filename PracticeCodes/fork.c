#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
    pid_t retValue;
    printf("The process id is: %d\n",getpid());
    retValue=fork();
    if (retValue<0){
        printf("\nFork Failed!");
    }else if(retValue==0){
        sleep(2);
        printf("\nChild Process:\n");
        printf("The process id is:%d\n",getpid());
    }else{
        wait();// this waits for the child process to complete
        sleep(4);
        printf("Parent Process:\n");
        printf("The process id is:%d\n",getpid());
    }
    return 0;
}