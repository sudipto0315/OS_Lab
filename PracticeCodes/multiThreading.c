#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
int sum;
void *runner(void *param){
    int i, num = atoi(param); // atoi converts string to integer
    sum = 0;
    for(i=0; i<num; i++){
        sum += i;
    }
    pthread_exit(0);
}
int main(int argc, char *argv[]){
    pthread_t tid; // thread identifier
    pthread_attr_t attr; // set of thread attributes
    if(argc!=2){
        fprintf(stderr, "usage: ./a.out <integer value>\n");
        return -1;
    }
    if(atoi(argv[1])<0){ // atoi converts string to integer
        fprintf(stderr, "%d must be >=0\n", atoi(argv[1]));
        return -1;
    }
    pthread_attr_init(&attr); // get default attributes
    pthread_create(&tid, &attr, runner, argv[1]); // create the thread
    pthread_join(tid, NULL); // wait for the thread to exit // NULL is the return value
    printf("sum = %d\n", sum);
    return 0;
}