# Producer-Consumer Project
This project is a simple implementation of the Producer-Consumer problem using C programming language. It includes two main files: project.c which contains the main program, and buffer.h which has the definition and operations for the buffer used in the project.


## Main Project Files
### **project.c**
This is the main program file. It includes a main function that creates producer and consumer threads. Each producer and consumer is simulated as a thread and they communicate via a shared buffer.

void* producer(void* args): This function represents the behavior of the producer threads. It generates a random number between 0 and 99, simulating the production of an item. The function then safely inserts this item into the shared buffer.

void* consumer(void* args): This function represents the behavior of the consumer threads. It safely removes an item from the shared buffer and then consumes it.

### **buffer.h**
This header file contains the definition of the buffer and operations for managing it. It also includes mutexes and semaphores for safely manipulating the buffer.

void displayBuffer(): This function prints the current state of the buffer along with the number of items produced (In) and consumed (Out).

void insertItem(int item): This function is used to safely insert an item into the buffer.

int removeItem(): This function safely removes an item from the buffer and returns it.

## Installation and Running
The program is a simple C code. It can be compiled and run using gcc (or any C compiler).

Here's an example using gcc:

```
$ gcc project.c -o project -lpthread
$ ./project <sleep_time> <producer_threads_count> <consumer_threads_count>
```
> sleep_time is the time in seconds that the main thread will sleep before finishing.

producer_threads_count is the number of producer threads to be created.

consumer_threads_count is the number of consumer threads to be created.

Please note that you should not exceed MAX_THREADS, which is set to 8 in this project.

During the submission of the project, the output out of the code had to go through a program to clean the typescript file to readable text using 'script2txtkb.cpp' (not made by me).

## Key Concepts
Producer-Consumer Problem: This is a classic example of a multi-process synchronization problem. It describes two processes, the producer and the consumer, which share a common, fixed-size buffer used as a queue.

Thread: A thread is a single sequence stream within in a process. Threads have same properties as of the process so they are called as light weight processes. Threads are executed one after another but gives the illusion as if they are executing in parallel.

Mutex: Mutex is a lock that we set before using a shared resource and release after using it. When the lock is set, no other thread can access the locked region of code.

Semaphore: Semaphore is simply a variable that is non-negative and shared between threads. A semaphore is a signaling mechanism, and a thread that is waiting on a semaphore can be signaled by another thread.
