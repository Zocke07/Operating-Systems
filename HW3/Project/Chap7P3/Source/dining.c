#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
pthread_cond_t forks[NUM_PHILOSOPHERS];

typedef struct {
    int id;
} Philosopher;

void *philosopher_thread(void *arg) {
    Philosopher *philosopher = (Philosopher *)arg;
    int id = philosopher->id;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 3 + 1);

        // Hungry, try to eat
        printf("Philosopher %d is hungry.\n", id);
        pthread_mutex_lock(&chopsticks[id]);
        pthread_mutex_lock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 3 + 1);

        // Finished eating, return forks
        printf("Philosopher %d finished eating.\n", id);
        pthread_mutex_unlock(&chopsticks[id]);
        pthread_mutex_unlock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
    }
    
    return NULL;
}

int main() {
    srand(time(NULL));

    // Initialize mutexes and conditions
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    Philosopher philosophers[NUM_PHILOSOPHERS];
    pthread_t threads[NUM_PHILOSOPHERS];

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].id = i;
        pthread_create(&threads[i], NULL, philosopher_thread, &philosophers[i]);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutexes and conditions
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
