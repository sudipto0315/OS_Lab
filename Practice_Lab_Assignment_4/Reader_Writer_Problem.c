#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_READERS 5
#define NUM_WRITERS 5

sem_t mutex;
sem_t db;
int reader_count;

void *reader(void *param) {
    int id = *((int *)param);
    while(1) {
        sem_wait(&mutex);
        reader_count++;
        if(reader_count == 1) {
            sem_wait(&db);
        }
        sem_post(&mutex);
        printf("Reader %d reads\n", id);
        sleep(1);
        sem_wait(&mutex);
        reader_count--;
        if(reader_count == 0) {
            sem_post(&db);
        }
        sem_post(&mutex);
    }
}

void *writer(void *param) {
    int id = *((int *)param);
    while(1) {
        sem_wait(&db);
        printf("Writer %d writes\n", id);
        sleep(1);
        sem_post(&db);
    }
}

int main() {
    int i;
    int ids[NUM_READERS + NUM_WRITERS];
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);
    reader_count = 0;

    for(i = 0; i < NUM_READERS; i++) {
        ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }
    for(i = 0; i < NUM_WRITERS; i++) {
        ids[NUM_READERS + i] = i;
        pthread_create(&writers[i], NULL, writer, &ids[NUM_READERS + i]);
    }

    for(i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for(i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}