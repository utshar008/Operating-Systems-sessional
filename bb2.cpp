#include <iostream>
#include <queue>
#include <pthread.h>  // Include the pthread header for threads
#include <semaphore.h>
#include <unistd.h>   // Include for sleep function

using namespace std;

queue<int> buffer;
sem_t emptySlots;
sem_t fullSlots;

void *producer(void *) {  // Change the function signature to match pthread_create
    for (int i = 1; i <= 5; ++i) {
        sem_wait(&emptySlots);
        buffer.push(i);
        cout << "Produced: " << i << endl;
        sem_post(&fullSlots);
        usleep(500 * 1000);  // Use usleep for sleeping (500 milliseconds)
    }
    pthread_exit(NULL);  // Exit the thread
}

void *consumer(void *) {  // Change the function signature to match pthread_create
    while (true) {
        sem_wait(&fullSlots);
        int data = buffer.front();
        buffer.pop();
        cout << "Consumed: " << data << endl;
        sem_post(&emptySlots);
        usleep(1000 * 1000);  // Use usleep for sleeping (1000 milliseconds)
    }
    pthread_exit(NULL);  // Exit the thread
}

int main() {
    // Max 5 empty slots
    sem_init(&emptySlots, 0, 5);
    // Initially, no full slots in the buffer
    sem_init(&fullSlots, 0, 0);

    pthread_t producerThread, consumerThread;  // Declare pthread_t variables

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);

    return 0;
}
