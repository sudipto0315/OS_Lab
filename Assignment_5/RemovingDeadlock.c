#include <stdio.h>
#include <malloc.h>

typedef struct {
    int numberOfProcesses;
    int numberOfDistinctResources;

    int *availableResources;
    int numberOfCompletedProcesses;
    int numberOfTerminatedProcesses;
    int *terminatedProcesses;
    int *completedProcesses;
    int **allocatedResources;
    int **requiredResources;

} Info;

Info *readFile(char *filename) {
    FILE *input_file = fopen(filename, "r");
    char input_buffer[255];

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    Info *info = malloc(sizeof(Info));


    int numberOfDistinctResources;
    fscanf(input_file, "%d ", &numberOfDistinctResources);
    info->numberOfDistinctResources = numberOfDistinctResources;
    printf("%d\n", numberOfDistinctResources);

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    info->availableResources = malloc(sizeof(int) * info->numberOfDistinctResources);
    for (int i = 0; i < info->numberOfDistinctResources; i++) {
        int temp;
        fscanf(input_file, "%d ", &temp);
        info->availableResources[i] = temp;
        printf("%d ", temp);
    }
    printf("\n");

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    int numberOfProcesses;
    fscanf(input_file, "%d ", &numberOfProcesses);
    info->numberOfProcesses = numberOfProcesses;
    info->numberOfTerminatedProcesses = 0;
    info->terminatedProcesses = malloc(sizeof(int) * numberOfProcesses);
    info->numberOfCompletedProcesses = 0;
    info->completedProcesses = malloc(sizeof(int) * numberOfProcesses);
    printf("%d\n", numberOfProcesses);

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    info->allocatedResources = malloc(sizeof(int *) * numberOfProcesses);

    for (int i = 0; i < info->numberOfProcesses; i++) {
        info->allocatedResources[i] = malloc(sizeof(int) * numberOfDistinctResources);
        for (int j = 0; j < info->numberOfDistinctResources; j++) {
            int temp;
            fscanf(input_file, "%d ", &temp);
            info->allocatedResources[i][j] = temp;
            printf("%d ", temp);
        }
        printf("\n");
    }

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    info->requiredResources = malloc(sizeof(int *) * numberOfProcesses);

    for (int i = 0; i < info->numberOfProcesses; i++) {
        info->requiredResources[i] = malloc(sizeof(int) * numberOfDistinctResources);
        for (int j = 0; j < info->numberOfDistinctResources; j++) {
            int temp;
            fscanf(input_file, "%d ", &temp);
            info->requiredResources[i][j] = temp;
            printf("%d ", temp);
        }
        printf("\n");
    }


    return info;

}

Info *deepCopy(Info* source) {



    Info *info = malloc(sizeof(Info));

    info->numberOfDistinctResources = source->numberOfDistinctResources;


    info->availableResources = malloc(sizeof(int) * info->numberOfDistinctResources);
    for (int i = 0; i < info->numberOfDistinctResources; i++) {

        info->availableResources[i] = source->availableResources[i];
    }


    info->numberOfProcesses = source->numberOfProcesses;
    info->numberOfTerminatedProcesses = source->numberOfTerminatedProcesses;
    info->terminatedProcesses = malloc(sizeof(int) * info->numberOfProcesses);
    for(int i = 0; i < info->numberOfTerminatedProcesses;i++){
        info->terminatedProcesses[i] = source->terminatedProcesses[i];
    }

    info->numberOfCompletedProcesses = 0;
    info->completedProcesses = malloc(sizeof(int) * info->numberOfProcesses);


    info->allocatedResources = malloc(sizeof(int *) * info->numberOfProcesses);

    for (int i = 0; i < info->numberOfProcesses; i++) {
        info->allocatedResources[i] = malloc(sizeof(int) * info->numberOfDistinctResources);
        for (int j = 0; j < info->numberOfDistinctResources; j++) {
            info->allocatedResources[i][j] = source->allocatedResources[i][j];
        }
    }



    info->requiredResources = malloc(sizeof(int *) * info->numberOfProcesses);

    for (int i = 0; i < info->numberOfProcesses; i++) {
        info->requiredResources[i] = malloc(sizeof(int) * info->numberOfDistinctResources);
        for (int j = 0; j < info->numberOfDistinctResources; j++) {
            info->requiredResources[i][j] = source->requiredResources[i][j];
        }
    }


    return info;

}

void destroy(Info *info) {
    free(info->allocatedResources);
    free(info->requiredResources);

    free(info->completedProcesses);
    free(info->terminatedProcesses);
}

int isFinishedProcess(Info *info, int processIndex) {
    for (int i = 0; i < info->numberOfCompletedProcesses; i++) {
        if (processIndex == info->completedProcesses[i]) {
            return 1;
        }
    }

    for (int i = 0; i < info->numberOfTerminatedProcesses; i++) {
        if (processIndex == info->terminatedProcesses[i]) {
            return 1;
        }
    }
    return 0;
}


int isDeadlocked(Info* info) {
    int prevNumberOfFinishedProcesses = 0;
    while (1) {
        if (info->numberOfCompletedProcesses + info->numberOfTerminatedProcesses == info->numberOfProcesses) break;


        for (int processIndex = 0; processIndex < info->numberOfProcesses; processIndex++) {

            if (isFinishedProcess(info, processIndex)) continue;


            int satisfies = 1;
            for (int resourceNumber = 0; resourceNumber < info->numberOfDistinctResources; resourceNumber++) {
                if (info->availableResources[resourceNumber] < info->requiredResources[processIndex][resourceNumber]) {
                    satisfies = 0;
                    break;
                }
            }
            if (satisfies) {
                // printf("Process Number %d will get executed\n", processIndex);
                info->completedProcesses[info->numberOfCompletedProcesses++] = processIndex;
                for (int resourceNumber = 0; resourceNumber < info->numberOfDistinctResources; resourceNumber++) {
                    info->availableResources[resourceNumber] += info->allocatedResources[processIndex][resourceNumber];
                }
            }


        }
        if (prevNumberOfFinishedProcesses == info->numberOfTerminatedProcesses + info->numberOfCompletedProcesses) {
            //printf("DeadLock Detected\n");
            return 1;


        }
        prevNumberOfFinishedProcesses = info->numberOfTerminatedProcesses + info->numberOfCompletedProcesses;
    }
    return 0;
}


int main() {
    Info *info = readFile("/Users/georgerahul/Desktop/OS-Lab/Assignment 4/input.txt");
    int firstTime=0;
    while (1){
        Info *copy_info = deepCopy(info);
        if(!isDeadlocked(copy_info)) break;
        firstTime++;
        for(int procNo=0;procNo<info->numberOfProcesses;procNo++){
            if(isFinishedProcess(info,procNo)) continue;
            Info* temp_info = deepCopy(info);
            temp_info->terminatedProcesses[temp_info->numberOfTerminatedProcesses++] = procNo;

            for (int resourceNumber = 0; resourceNumber < temp_info->numberOfDistinctResources; resourceNumber++) {
                temp_info->availableResources[resourceNumber] += temp_info->allocatedResources[procNo][resourceNumber];

            }


            //printf("Trying to remove process Number %d  ",procNo);

            if(!isDeadlocked(temp_info)){
                printf("Removing Process Number: %d\n",procNo);
                fflush(stdin);
                info->terminatedProcesses[info->numberOfTerminatedProcesses++]=procNo;
                for (int resourceNumber = 0; resourceNumber < temp_info->numberOfDistinctResources; resourceNumber++) {
                    temp_info->availableResources[resourceNumber] += temp_info->allocatedResources[procNo][resourceNumber];

                }



                break;
            }

        }

    }
    if (firstTime==0){
        printf("No DeadLock");
    } else{
        printf("Deadlocked Freed");
    }

    destroy(info);


}