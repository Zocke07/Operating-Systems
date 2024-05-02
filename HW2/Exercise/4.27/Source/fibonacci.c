#include <stdio.h>
#include <pthread.h>

int fibSequence[100];
int fibLength;

void *generateFibonacci(void *arg) {
    int n = *((int *) arg);

    fibSequence[0] = 0;
    fibSequence[1] = 1;
    fibLength = 2;

    for (int i = 2; i < n; i++) {
        fibSequence[i] = fibSequence[i - 1] + fibSequence[i - 2];
        fibLength++;
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

    pthread_join(tid, NULL);

    printf("Fibonacci sequence:\n");
    for (int i = 0; i < fibLength; i++) {
        printf("%d ", fibSequence[i]);
    }
    printf("\n");

    return 0;
}
