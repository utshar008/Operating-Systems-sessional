#include <bits/stdc++.h>
#include <queue>
#include <semaphore.h>

using namespace std;

queue<int> buffer;
sem_t emptySlots;
sem_t fullSlots;

void producer() {
   for (int i = 1; i <= 5; ++i) {
      sem_wait(&emptySlots);
      buffer.push(i);
      cout << "Produced: " << i << endl;
      sem_post(&fullSlots);
   }
}

void consumer() {
   for (int i = 1; i <= 5; ++i) {
      sem_wait(&fullSlots);
      int data = buffer.front();
      buffer.pop();
      cout << "Consumed: " << data << endl;
      sem_post(&emptySlots);
   }
}

int main() {
   // Max 5 empty slots
   sem_init(&emptySlots, 0, 5);
   // Initially, no full slots in the buffer
   sem_init(&fullSlots, 0, 0);

   producer();


   consumer();

   sem_destroy(&emptySlots);
   sem_destroy(&fullSlots);

   return 0;
}
