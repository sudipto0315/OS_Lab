#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
    pid_t retValue;
    int n,a,b;
    printf("The process id is: %d\n",getpid());
    retValue=fork();
    if (retValue<0){
        printf("\nFork Failed!");
    }else if(retValue==0){
        // child process
        printf("\n**** Child Process ****\n");
        printf("The process id is:%d and the parent process id is:%d\n",getpid(),getppid());
        printf("Enter a number to check even or odd\n");
        scanf("%d",&n);
        if(n%2==0){
            printf("The number %d is even\n",n);
        }else{
            printf("The number %d is odd\n",n);
        }

    }else{
        // parent process
        wait();// this waits for the child process to complete
        printf("\n**** Parent Process ****\n");
        printf("The process id is:%d\n",getpid());
        printf("Enter a number to check max or min\n");
        scanf("%d%d",&a,&b);
        if(a>b){
            printf("The number %d is greater than %d\n",a,b);
        }else{
            printf("The number %d is greater than %d\n",b,a);
        }
    }
    return 0;
}