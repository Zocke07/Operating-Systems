#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_FARMERS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int northbound_count = 0;
int southbound_count = 0;

void* northbound_farmer(void* arg) {
    int id = *((int*)arg);
    
    pthread_mutex_lock(&mutex);
    while (southbound_count > 0) {
        pthread_mutex_unlock(&mutex);
        printf("Northbound Farmer %d is waiting.\n", id);
        usleep(100000);
        pthread_mutex_lock(&mutex);
    }
    northbound_count++;
    pthread_mutex_unlock(&mutex);
    
    printf("Northbound Farmer %d is crossing the bridge.\n", id);
    usleep(rand() % 1000000);
    
    pthread_mutex_lock(&mutex);
    northbound_count--;
    pthread_mutex_unlock(&mutex);
    
    printf("Northbound Farmer %d has crossed the bridge.\n", id);
    return NULL;
}

void* southbound_farmer(void* arg) {
    int id = *((int*)arg);
    
    pthread_mutex_lock(&mutex);
    while (northbound_count > 0) {
        pthread_mutex_unlock(&mutex);
        printf("Southbound Farmer %d is waiting.\n", id);
        usleep(100000);
        pthread_mutex_lock(&mutex);
    }
    southbound_count++;
    pthread_mutex_unlock(&mutex);
    
    printf("Southbound Farmer %d is crossing the bridge.\n", id);
    usleep(rand() % 1000000);
    
    pthread_mutex_lock(&mutex);
    southbound_count--;
    pthread_mutex_unlock(&mutex);
    
    printf("Southbound Farmer %d has crossed the bridge.\n", id);
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t northbound_threads[MAX_FARMERS];
    pthread_t southbound_threads[MAX_FARMERS];
    int northbound_ids[MAX_FARMERS];
    int southbound_ids[MAX_FARMERS];
    int i;
    
    for (i = 0; i < MAX_FARMERS; i++) {
        northbound_ids[i] = i + 1;
        southbound_ids[i] = i + 1;
        pthread_create(&northbound_threads[i], NULL, northbound_farmer, &northbound_ids[i]);
        pthread_create(&southbound_threads[i], NULL, southbound_farmer, &southbound_ids[i]);
    }
    
    for (i = 0; i < MAX_FARMERS; i++) {
        pthread_join(northbound_threads[i], NULL);
        pthread_join(southbound_threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
