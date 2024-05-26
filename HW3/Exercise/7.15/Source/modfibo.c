#include <stdio.h>
#include <pthread.h>

int fibSequence[100];
int fibLength = 0;
pthread_mutex_t fibMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fibCond = PTHREAD_COND_INITIALIZER;

void *generateFibonacci(void *arg) {
    int n = *((int *) arg);

    fibSequence[0] = 0;
    fibSequence[1] = 1;
    fibLength = 2;

    pthread_mutex_lock(&fibMutex);
    pthread_cond_signal(&fibCond);
    pthread_mutex_unlock(&fibMutex);

    for (int i = 2; i < n; i++) {
        int nextFib;
        pthread_mutex_lock(&fibMutex);
        nextFib = fibSequence[i - 1] + fibSequence[i - 2];
        fibSequence[i] = nextFib;
        fibLength++;
        pthread_cond_signal(&fibCond);
        pthread_mutex_unlock(&fibMutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int n;

    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Enter a number more than 0");
        return 1;
    }

    pthread_create(&tid, NULL, generateFibonacci, &n);

    printf("Fibonacci sequence:\n");
    pthread_mutex_lock(&fibMutex);
    while (fibLength < 2) {
        pthread_cond_wait(&fibCond, &fibMutex);
    }
    for (int i = 0; i < fibLength; i++) {
        printf("%d ", fibSequence[i]);
    }
    printf("\n");
    pthread_mutex_unlock(&fibMutex);

    pthread_join(tid, NULL);

    return 0;
}
