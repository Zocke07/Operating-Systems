#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

typedef struct {
    int *arr;
    int size;
} SubList;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void* sortSublist(void* arg) {
    SubList* sublist = (SubList*)arg;
    mergeSort(sublist->arr, 0, sublist->size - 1);
    pthread_exit(NULL);
}

void* mergeSublists(void* arg) {
    int* arr = (int*)arg;
    merge(arr, 0, SIZE / 2 - 1, SIZE - 1);
    pthread_exit(NULL);
}

void printSublist(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[SIZE] = {12, 24, 6, 32, 9, 11, 7, 42, 43, 77};
    
    printf("Elements of the array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");


    pthread_t tid[3];
    SubList sublists[2];

    sublists[0].arr = arr;
    sublists[0].size = SIZE / 2;
    sublists[1].arr = arr + SIZE / 2;
    sublists[1].size = SIZE / 2;

    printf("Divided sublists:\n");
    for (int i = 0; i < 2; i++) {
        printSublist(sublists[i].arr, sublists[i].size);
    }

    for (int i = 0; i < 2; i++) {
        pthread_create(&tid[i], NULL, sortSublist, &sublists[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("Sorted sublists:\n");
    for (int i = 0; i < 2; i++) {
        printSublist(sublists[i].arr, sublists[i].size);
    }

    pthread_create(&tid[2], NULL, mergeSublists, arr);

    pthread_join(tid[2], NULL);

    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
