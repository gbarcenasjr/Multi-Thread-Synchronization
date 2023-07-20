#ifndef __buffer__h
#define __buffer__h

#include <pthread.h>
#include <semaphore.h>

#define MAX_BUF_LEN 5

int buffer[MAX_BUF_LEN];
int count = 0;
int inCounter = 0, outCounter = 0;

pthread_mutex_t mutexBuffer;
sem_t semEmpty;
sem_t semFull;

void displayBuffer()
{
    int i;
    for(i = 0; i < count; i++)
    {
        printf("[%d] ", buffer[i]);
    }
    for(i = count; i < MAX_BUF_LEN; i++)
    {
        printf("[ ] ");
    }
    printf("In = %d, Out = %d\n", inCounter, outCounter);
}

void insertItem(int item)
{
    // Add item to the buffer
    sem_wait(&semEmpty);
    pthread_mutex_lock(&mutexBuffer);
    buffer[count] = item;
    printf("Inserted item %d at position %d\n", item, count);    
    count++;
    inCounter++;
    pthread_mutex_unlock(&mutexBuffer);
    sem_post(&semFull);
}

int removeItem()
{
    int item;

    // Remove item from the buffer
    sem_wait(&semFull);
    pthread_mutex_lock(&mutexBuffer);
    item = buffer[count - 1];
    printf("Removed item %d from position %d\n", item, count);    
    count--;
    pthread_mutex_unlock(&mutexBuffer);
    sem_post(&semEmpty);
    return item;
}

#endif
