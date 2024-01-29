#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/types.h>
int main(int argc,char *argv[]) {
    if(argc!=3) {
        fprintf(stderr,"Usage: %s <inputfile> <outputfile>\n",argv[0]);
        exit(1);
    }
    int readFD,writeFD;
    readFD=open(argv[1],O_RDONLY);
    writeFD=open(argv[2],O_WRONLY|O_CREAT,0644);
    int pipe1[2],pipe2[2];
    if(pipe(pipe1)==-1||pipe(pipe2)==-1) {
        fprintf(stderr,"Error while creating the pipes\n");
        exit(1);
    }
    if(readFD != -1 && writeFD != -1){
        //dup the stdin and stdout
        dup2(readFD,STDIN_FILENO);
        dup2(writeFD,STDOUT_FILENO);
    }

    pid_t child1,child2;
    if ((child1=fork())==0) {
        // Child 1
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);
        dup2(readFD,STDIN_FILENO);
        dup2(pipe1[1],STDOUT_FILENO);
        char c;
        while((c=getchar())!=EOF) {
            write(pipe1[1],&c,1);
        }
        exit(0);
    }else if((child2=fork())==0) {
            // Child 2 
            close(pipe1[1]);
            close(pipe2[0]);
            char c;
            while(read(pipe1[0],&c,1)>0) {
                c++;
                write(pipe2[1],&c,1);
            }
            exit(0);
    }else{
        // Parent
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);
        char c;
        while(read(pipe2[0],&c,1)>0) {
            c--;
            putchar(c);
        }
        kill(child1,SIGTERM);
        kill(child2,SIGTERM);
        printf("\nChild processes terminated\n");\
        fprintf(stderr,"The output is in the file %s\n",argv[2]);
        exit(0);  
    }      
    return 0;
}