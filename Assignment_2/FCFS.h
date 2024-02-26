#include "process.h"

void FCFS(char *filename){
    int currentTime=0;
    int currentProcessNumber=0;
    ProcessArray *processTable=readProcessesFromFile(filename);
    while (currentProcessNumber<processTable->numberOfProcesses){
        Process *currentProcess=processTable->processes[currentProcessNumber];
        if(currentTime>currentProcess->arrival){
            //This means that the process has already arrived
            currentProcess->wait=currentTime-currentProcess->arrival;
            currentProcess->turnaround=currentProcess->wait+currentProcess->cpuBurst;
        }else{
            //This means that we have to increase the current time to match the next arrival time.
            //This is because process arrive in order
            currentTime=currentProcess->arrival;
            currentProcess->wait=0;
            currentProcess->turnaround=currentProcess->cpuBurst;
        }
        currentProcessNumber++;
        currentTime+=currentProcess->cpuBurst;
        currentProcess->timeCompleted=currentTime;
    }
    printProcessTable(processTable);
    printStatistics(processTable);
}