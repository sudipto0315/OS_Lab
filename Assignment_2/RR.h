#include "process.h"

void RR(char *filename,int timeQuantum){
    int RRTime=timeQuantum;
    int currentTime=0;
    int completedProcess=0;
    ProcessArray *pa=readProcessesFromFile(filename);
    while(completedProcess<pa->numberOfProcesses){
        int noActiveProcess=1;
        for(int i=0;i<pa->numberOfProcesses;i++){
            Process *cp=pa->processes[i];
            if(cp->arrival<=currentTime && cp->finished==0){
                noActiveProcess=0;
                int timeLeft=cp->cpuBurst-cp->timeRecieved;
                if(timeLeft<=RRTime){
                    cp->wait+=(currentTime-cp->lastWaitQueueEntryTime);
                    currentTime+=timeLeft;
                    cp->finished=1;
                    cp->turnaround=currentTime-cp->arrival;
                    cp->timeRecieved+=RRTime;
                    cp->timeCompleted=currentTime;
                    printf("[%d - %d]",currentTime-timeLeft,currentTime);
                    completedProcess+=1;
                    cp->lastWaitQueueEntryTime=currentTime;
                }else{
                    cp->wait+=(currentTime-cp->lastWaitQueueEntryTime);
                    currentTime+=RRTime;
                    cp->timeRecieved+=RRTime;
                    printf("[%d - %d] ",currentTime-RRTime,currentTime);
                    cp->lastWaitQueueEntryTime=currentTime;
                }
                printf("%s running currently\n",cp->name);
            }
        }
        if(noActiveProcess){
            currentTime+=1;
            printf("[%d] No active process\n",currentTime-1);
        }
    }
    printProcessTable(pa);
    printStatistics(pa);
}