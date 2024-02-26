#include "process.h"
#include <stdint.h>
Process *findMinNonCompleted(ProcessArray *pa, int currentTime){
    int minBurstTime=INT32_MAX;
    Process *minProcess=NULL;
    for(int i=0;i<pa->numberOfProcesses;i++){
        Process *temp=pa->processes[i];
        int remainingBurstTime=temp->cpuBurst-temp->timeRecieved;
        if(remainingBurstTime<minBurstTime && temp->finished==0 && temp->arrival<=currentTime){
            minProcess=temp;
            minBurstTime=remainingBurstTime;
        }
    }
    return minProcess;
}
void SRBF(char *filename){
    int currentTime=0;
    int completedProcess=0;
    ProcessArray *pa=readProcessesFromFile(filename);
    while (completedProcess<pa->numberOfProcesses){
        Process *p=findMinNonCompleted(pa,currentTime);
        if(p!=NULL){
            p->timeRecieved+=1;
            printf("%s is executing at time %d\n",p->name,currentTime);
            if((p->cpuBurst-p->timeRecieved)==0){
                p->finished=1;
                p->timeCompleted=currentTime+1;
                p->turnaround=p->timeCompleted-p->arrival;
                p->wait=p->turnaround-p->cpuBurst;
                completedProcess+=1;
            }
        }
        currentTime+=1;
    }
    printProcessTable(pa);
    printStatistics(pa);
}
