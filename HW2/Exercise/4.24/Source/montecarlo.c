#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 10

int circle = 0;
int square = 0;

void *count(void *arg) {
  int *n_ptr = (int *)arg;
  int n = *n_ptr;

  for (int i = 0; i < n; i++) {
    double x = (double)rand() / RAND_MAX;
    double y = (double)rand() / RAND_MAX;

    if (x * x + y * y <= 1) {
      circle++;
    }
    square++;
  }
  return NULL;
}

int main() {
  int total_points;
  printf("Enter the number of points to generate (-1 for random): ");
  scanf("%d", &total_points);

  if (total_points == -1) {
    srand(time(NULL));
    total_points = rand() % 1000000 + 1; // Random number of points between 1 and 1,000,000
    printf("Random number of points: %d\n", total_points);
  }

  pthread_t threads[NUM_THREADS];
  int points_per_thread = total_points / NUM_THREADS;

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, count, &points_per_thread);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("Approximation of Pi: %lf\n", 4.0 * circle / square);

  return 0;
}