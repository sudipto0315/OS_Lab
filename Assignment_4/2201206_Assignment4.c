#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int total_resources;
int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int processes;

bool is_safe_state(int work[], bool finish[], int need[][MAX_RESOURCES]) {
    bool can_finish;
    do {
        can_finish = false;
        for (int i = 0; i < processes; ++i) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < total_resources; ++j) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < total_resources; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    can_finish = true;
                }
            }
        }
    } while (can_finish);

    for (int i = 0; i < processes; ++i) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

void detect_deadlock() {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < total_resources; ++i) {
        work[i] = available[i];
    }
    int need[MAX_PROCESSES][MAX_RESOURCES];
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < total_resources; ++j) {
            need[i][j] = request[i][j] - allocation[i][j];
        }
    }

    bool deadlock_detected = true;
    int deadlock_processes[MAX_PROCESSES];
    int deadlock_count = 0;

    for (int i = 0; i < processes; ++i) {
        if (!finish[i]) {
            bool can_allocate = true;
            for (int j = 0; j < total_resources; ++j) {
                if (need[i][j] > work[j]) {
                    can_allocate = false;
                    break;
                }
            }
            if (can_allocate) {
                for (int j = 0; j < total_resources; ++j) {
                    work[j] += allocation[i][j];
                }
                finish[i] = true;
                if (is_safe_state(work, finish, need)) {
                    deadlock_detected = false;
                    break;
                } else {
                    deadlock_processes[deadlock_count++] = i;
                    finish[i] = false;
                    for (int j = 0; j < total_resources; ++j) {
                        work[j] -= allocation[i][j];
                    }
                }
            }
        }
    }

    if (deadlock_detected) {
        printf("Deadlock Detected\n");
        printf("Processes in Deadlock: ");
        for (int i = 0; i < deadlock_count; ++i) {
            printf("%d ", deadlock_processes[i]);
        }
        printf("\n");
    } else {
        printf("No Deadlock Detected\n");
    }
}

int main() {
    printf("Enter the total number of distinct resources: ");
    scanf("%d", &total_resources);
    printf("Enter the number of instances of each resource type: ");
    for (int i = 0; i < total_resources; ++i) {
        scanf("%d", &available[i]);
    }
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < total_resources; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter the request matrix:\n");
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < total_resources; ++j) {
            scanf("%d", &request[i][j]);
        }
    }

    detect_deadlock();

    return 0;
}
