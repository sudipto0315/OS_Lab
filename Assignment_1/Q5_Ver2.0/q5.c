#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<wait.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
    if(argc!=3){
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        exit(1);
    }
    int readFD=open(argv[1],O_RDONLY,0644);
    int writeFD=creat(argv[2],0644);
    if(readFD==-1 && writeFD==-1){
        //dup the stdin and stdout
        dup2(readFD,STDIN_FILENO);
        dup2(writeFD,STDOUT_FILENO);
    }
    int pipe_fd[2];
    if(pipe(pipe_fd)==-1){
        fprintf(stderr,"Error creating pipe");
        exit(1);
    }
    pid_t count_pid,convert_pid;
    if((count_pid=fork())==0){
        // this is for the count
        // the program that reads from pipe must be called first
        close(pipe_fd[1]); // this is to close the write end to indicate the EOF
        dup2(pipe_fd[0],STDIN_FILENO); // count should read from pipe 0
        dup2(writeFD,STDOUT_FILENO); // count should write to write file
        execl("count.o","count",(char *)NULL);
        perror("Error when running count.o");
        exit(1);
    }else if((convert_pid==fork())==0){
        dup2(pipe_fd[1],STDOUT_FILENO);
        dup2(readFD,STDIN_FILENO);
        execl("convert.o","convert",(char *)NULL);
        perror("Error when running convert.o");
        exit(1);
    }else{
        close(pipe_fd[1]);
        waitpid(count_pid,NULL,0);
        waitpid(convert_pid,NULL,0);
        exit(0);
    }
    return 0;
}