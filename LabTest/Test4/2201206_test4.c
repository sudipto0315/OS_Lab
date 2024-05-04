#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<ctype.h>

#define MAX_LEN 1000

char Input[MAX_LEN];
char Output[MAX_LEN];
int n;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
int current_index = 0;

void* convert_case(void* arg){
    int thread_id=*((int*)arg);
    while (1){
        pthread_mutex_lock(&mutex);
        int index=current_index++;
        pthread_mutex_unlock(&mutex);
        if(index>=strlen(Input)){
            break;
        }
        char ch=Input[index];
        if(islower(ch)){
            ch=toupper(ch);
        }else if(isupper(ch)){
            ch=tolower(ch);
        }
        Output[index]=ch;
    }
    return NULL;
}
int main(){
    printf("Enter a sentence: ");
    fgets(Input,MAX_LEN,stdin);
    printf("Enter the number of threads: ");
    scanf("%d",&n);
    pthread_t threads[n];
    int thread_ids[n];
    for(int i=0;i<n;i++){
        thread_ids[i]=i;
        pthread_create(&threads[i],NULL,convert_case,&thread_ids[i]);
    }
    for(int i=0;i<n;i++){
        pthread_join(threads[i],NULL);
    }
    printf("Converted sentence: %s\n",Output);
    return 0;
}