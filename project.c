#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#include "buffer.h"

#define TRUE 1

#define MAX_THREADS 8

void* producer(void* args) {
    while (TRUE) {

        // Produce an item
        // here a random number is genererated between 0 and 99
        int x = rand() % 100;
        // this sleep models the production time, change this to study
        // the effect of increase and decrease in production time
        int rand_time = rand() % 5; // random time between 0 and 4
        printf("Producer thread %ld sleeping for %d seconds\n",
            pthread_self(), rand_time);
        sleep(rand_time); 

        // insert the produced item safely to the buffer
        insertItem(x);

        // display the current state of the buffer
        displayBuffer();
        fflush(stdout);
    }
}

void* consumer(void* args) {
    while (TRUE) {
        int item;

        // Remove an item safely from the buffer
        item = removeItem();

        // Consume the item
        outCounter++;
        printf("Consumed %d\n", item);
        // this sleep models the consumption time, change this to study
        // the effect of increase and decrease in consumption time        
        int rand_time = rand() % 5; // random time between 0 and 4
        printf("Consumer thread %ld sleeping for %d seconds\n",
            pthread_self(), rand_time);
        sleep(rand_time); 

        displayBuffer();
        fflush(stdout);
    }
}

int main(int argc, char* argv[]) {
    printf("\nMain thread beginning\n\n");
    int i;
    int prodThreadCount=1, consThreadCount=1;
    int sleepTime = 1;
    pthread_t prodThreadIDs[MAX_THREADS];
    pthread_t consThreadIDs[MAX_THREADS];

    if(argc == 4)  {
        sleepTime = atoi(argv[1]);
        prodThreadCount = atoi(argv[2]);
        consThreadCount = atoi(argv[3]);
    }
    else {
        perror("Invalid number of arguments\n");
        exit(-1);
    }

    if(prodThreadCount>MAX_THREADS)
        perror("producer threads more than the MAX_THREADS\n");

    if(consThreadCount>MAX_THREADS)
        perror("consumer threads more than the MAX_THREADS\n");

    // necessary initialization
    srand(time(NULL));
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, MAX_BUF_LEN);
    sem_init(&semFull, 0, 0);

    // create producer threads
    for (i = 0; i < prodThreadCount; i++) {
        if (pthread_create(&prodThreadIDs[i], NULL, &producer, NULL) != 0) {
            perror("Failed to create thread");
        }
        else {
            printf("Creating producer thread with id %ld\n", prodThreadIDs[i]);
        }
    }

    // create consumer threads
    for (i = 0; i < consThreadCount; i++) {
        if (pthread_create(&consThreadIDs[i], NULL, &consumer, NULL) != 0) {
            perror("Failed to create thread");
        }
        else {
            printf("Creating consumer thread with id %ld\n", consThreadIDs[i]);
        }
    }

    // sleep for user specified time
    printf("Main thread sleeping for %d seconds\n", sleepTime);
    sleep(sleepTime);

    #if 0
    // join producer threads
    for (i = 0; i < prodThreadCount; i++) {
        if (pthread_join(prodThreadIDs[i], NULL) != 0) {
            perror("Failed to join producer thread");
        }
    }

    // join consumer threads
    for (i = 0; i < consThreadCount; i++) {
        if (pthread_join(consThreadIDs[i], NULL) != 0) {
            perror("Failed to join consumer thread");
        }
    }
    #endif

    // clean up the mess
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);

    //Exit the program
    printf("\nMain thread exiting after %d seconds\n\n", sleepTime);

    return 0;
}
