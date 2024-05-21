#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head = NULL;
struct node *current = NULL;
struct node *newNode = NULL;
struct node *finalNode = NULL;

void add(char *name, int priority, int burst) {
    if (head == NULL) {
        head = malloc(sizeof(struct node));

        // Set the properties of the task
        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->burst = burst;
        head->task->priority = priority;

        // Set the next node to be null
        head->next = NULL;

        current = head;
    } else {
        newNode = malloc(sizeof(struct node));

        newNode->task = malloc(sizeof(struct task));
        newNode->task->burst = burst;
        newNode->task->name = name;
        newNode->task->priority = priority;

        // If current->next is NULL
        if (!(current->next)) {
            if (((newNode->task->priority) <= (current->task->priority))) {
                current->next = newNode;
                newNode->next = NULL;
            } else {
                // Set newNode to point to head which is in the second position
                newNode->next = current;
                // Head now holds the address of newNode which is in the first position
                head = newNode;
                // Reset current to newNode
                current = newNode;
            }
        } else {
            while (1) {
                if ((newNode->task->priority > current->next->task->priority)) {
                    if (newNode->task->priority < current->task->priority) {
                        newNode->next = current->next;
                        current->next = newNode;
                        current = head;
                        break;
                    } else if (newNode->task->priority > current->task->priority) {
                        head = newNode;
                        newNode->next = current;
                        current = head;
                        break;
                    } else if (newNode->task->priority == current->task->priority) {
                        newNode->next = current->next;
                        current->next = newNode;
                        break;
                    }
                } else if (newNode->task->priority == current->next->task->priority) {
                    current = current->next;

                    if (current->next == NULL) {
                        newNode->next = NULL;
                    } else if (newNode->task->priority == current->next->task->priority) {
                        current = current->next;
                        newNode->next = current->next;
                    } else {
                        newNode->next = current->next;
                    }

                    current->next = newNode;
                    current = head;
                    break;
                } else if ((newNode->task->priority) < (current->next->task->priority)) {
                    current = current->next;

                    if (current->next == NULL) {
                        current->next = newNode;
                        newNode->next = NULL;
                        current = head;
                        break;
                    }
                }
            }
        }
    }
}

// Invoke the scheduler
void schedule() {
    int numTasks = 0;
    float avgResponseTime = 0;
    float avgTurnaroundTime = 0;
    float avgWaitTime = 0;
    int totalBurst = 0;

    struct node *ref = head;
    while (ref != NULL) {
        numTasks++;
        run(ref->task, ref->task->burst);
        totalBurst += ref->task->burst;
        avgTurnaroundTime += totalBurst;

        if (ref->next != NULL) {
            avgResponseTime += totalBurst;
        }
        ref = ref->next;
    }

    avgWaitTime = avgTurnaroundTime - totalBurst;

    printf("The average turnaround time is: %f time units\n", avgTurnaroundTime / numTasks);
    printf("The average ResponseTime is: %f time units\n", avgResponseTime / numTasks);
    printf("The average WaitTime is: %f time units\n", avgWaitTime / numTasks);
}
