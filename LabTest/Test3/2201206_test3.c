#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX 10
int array[MAX]={0};
int sorted_array[MAX]={0};

typedef struct{
    int start;
    int end;
}threadData;

void *sorter(void *parameters){
    threadData *p=(threadData *)parameters;
    int start=p->start;
    int end=p->end;
    for(int i=start;i<end;i++){
        for (int j=i+1;j<=end;j++){
            if(array[i]>array[j]){
                int temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
}
void merge(){
    int mid=MAX/2;
    int i=0,j=mid,k=0;
    while(i<mid && j<MAX){
        if(array[i]<array[j]){
            sorted_array[k++]=array[i++];
        }else{
            sorted_array[k++]=array[j++];
        }
    }
    while(i<mid){
        sorted_array[k++]=array[i++];
    }
    while(j<MAX){
        sorted_array[k++]=array[j++];
    }
}
int main(){
    pthread_t thread1,thread2;
    threadData p1,p2;
    printf("Enter 10 numbers: ");
    for(int i=0;i<MAX;i++){
        scanf("%d",&array[i]);
    }

    p1.start=0;
    p1.end=MAX/2-1;
    pthread_create(&thread1,NULL,sorter,&p1);

    p2.start=MAX/2;
    p2.end=MAX-1;
    pthread_create(&thread2,NULL,sorter,&p2);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    merge();
    printf("Sorted array: ");
    for(int i=0;i<MAX;i++){
        printf("%d ",sorted_array[i]);
    }
    printf("\n");
    return 0;
}