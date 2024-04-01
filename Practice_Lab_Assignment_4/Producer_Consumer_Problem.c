#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];  // shared buffer
int count = 0;  // number of items in the buffer

pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;

void* producer(void* param) {
    int item;
    while(1) {
        sleep(1);  // sleep for 1 second
        item = rand() % 100;  // generate a random item
        pthread_mutex_lock(&mutex);
        if(count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_producer, &mutex);
        }
        buffer[count] = item;
        count++;
        printf("Producer produced item %d\n", item);
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
    }
}

void* consumer(void* param) {
    int item;
    while(1) {
        pthread_mutex_lock(&mutex);
        if(count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        item = buffer[--count];
        printf("Consumer consumed item %d\n", item);
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
        sleep(1);  // sleep for 1 second
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}