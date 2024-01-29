#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void killChildren(int pid) {
    kill(pid, SIGINT);
}
void handler() {
    fprintf(stderr, "Handler is running\n");
    longjmp(env, 1);
}

int main(int argc,char *argv[]){
    int overlay=0;
    int readFile=0;
    int writeFile=0;
    int overlayIndex=-1;
    int readFileIndex=-1;
    int writeFileIndex=-1;
    argc-=1;
    if(argc==3){
        overlay=1;
        readFile=1;
        writeFile=1;
        overlayIndex=1;
        readFileIndex=2;
        writeFileIndex=3;
    }else if(argc==2){
        //Two Conditions
        if(argv[1][0]!='-'){
            readFile=1;
            readFileIndex=1;
            writeFile=1;
            writeFileIndex=2;
        }else{
            overlay=1;
            overlayIndex=1;
            readFile=1;
            readFileIndex=2;
        }
    }else if(argc==1){
        //One Condition
        if(argv[1][0]!='-'){
            readFile=1;
            readFileIndex=1;
        }else{
            overlay=1;
            overlayIndex=1;
        }
    }else{
        // No Condition
        // Nothing to write
    }
    printf("Overlay Status: %d || Overlay Index: %d\n", overlay, overlayIndex);

    printf("ReadFile Status: %d ||ReadFile Index: %d \n", readFile, readFileIndex);

    printf("WriteFile Status: %d || WriteFile Index: %d\n", writeFile, writeFileIndex);
    int readfd = STDIN_FILENO;
    if (readFile) {
        readfd = open(argv[readFileIndex], O_RDONLY, 0644);
    }

    int writefd = STDOUT_FILENO;

    if (writeFile) {
        writefd = creat(argv[writeFileIndex], 0644);
    }
    if (readfd != -1 && writefd != -1) {


        int oldstdin = dup(0);
        int oldstdout = dup(1);
        int pipe_fd[2];
        if (pipe(pipe_fd) < 0) {
            fprintf(stderr, "Pipe had some errors\n");
            exit(1);
        }

        signal(SIGALRM, handler);
        int count_pid, convert_pid;
        //count_pid is for count
        //convert_pid is for convert

        alarm(1);
        if((count_pid=fork())==0){
            close(pipe_fd[1]);
            dup2(pipe_fd[0],STDIN_FILENO);
            dup2(writefd,STDOUT_FILENO);
            if(overlay==1){
                printf("Overlay is there");
                execl("count.o","count",argv[overlayIndex], (char *) NULL);
            }else{
                execl("count.o","count",(char *)NULL);
            }
            perror("Error when running count.o");
            exit(1);
        }else if((convert_pid=fork())==0){
            dup2(pipe_fd[1],STDOUT_FILENO);
            dup2(readfd,STDIN_FILENO);
            execl("convert.o","convert",(char *)NULL);
            perror("Error when running convert.o");
            exit(1);
        }else{
            close(pipe_fd[1]);// This is to close the write end to indicate the EOF
            if(setjmp(env)!=0){
                // This means that the setjmp is not working properly
                //printf("SetJMP")
                killChildren(count_pid);
                killChildren(convert_pid);
                printf("Process ID of children are %d and %d\n", count_pid, convert_pid);
            }
            int status,pid;
            while ((pid = wait(&status)) > 0) {
                //This means that there is a child to wait for
                printf("Status is %d\n", status);
                fprintf(stderr, "child pid=%d reaped with exit status=%d\n",
                        pid, WEXITSTATUS(status));
                if (status != 0 && pid==count_pid) {
                    killChildren(count_pid);
                    killChildren(convert_pid);
                }
            }
        }
    }else{
        fprintf(stderr,"Error opening files");
        exit(1);
    }
    alarm(0);
    return 0;
}
