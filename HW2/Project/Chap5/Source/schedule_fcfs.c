#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head = NULL;
struct node *last = NULL;
struct node *newNode = NULL;
int numTasks = 0;

void add(char *name, int priority, int burst) {
    if (head == NULL) {
        head = malloc(sizeof(struct node));
        last = malloc(sizeof(struct node));

        // Set the properties of the task
        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->burst = burst;
        head->task->priority = priority;

        // Set the next node to be null
        head->next = NULL;
        last = head;
    } else {
        newNode = malloc(sizeof(struct node));
        last->next = newNode;
        newNode->task = malloc(sizeof(struct task));
        newNode->task->name = name;
        newNode->task->burst = burst;
        newNode->task->priority = priority;
        newNode->next = NULL;
        last = newNode;
    }
}

// Invoke the scheduler
void schedule() {
    int totalTime = 0;
    float avgTurnaroundTime = 0;
    float avgWaitTime = 0;
    float avgResponseTime = 0;

    struct node *current = head;

    while (current != NULL) {
        numTasks++;
        run(current->task, current->task->burst);

        totalTime += current->task->burst;

        avgTurnaroundTime += totalTime;

        if (current->next != NULL) {
            avgResponseTime += totalTime;
        }

        current = current->next;
    }

    avgWaitTime = avgTurnaroundTime - totalTime;

    printf("The average turnaround time is: %f time units\n", avgTurnaroundTime / numTasks);
    printf("The average ResponseTime is: %f time units\n", avgResponseTime / numTasks);
    printf("The average WaitTime is: %f time units\n", avgWaitTime / numTasks);
}
