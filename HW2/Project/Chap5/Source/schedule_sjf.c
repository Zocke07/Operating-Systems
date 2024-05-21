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
struct node *final = NULL;
int num = 0;

void add(char *name, int priority, int burst) {
    if (head == NULL) {
        head = malloc(sizeof(struct node));

        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->burst = burst;
        head->task->priority = priority;
        head->next = NULL;

        current = head;
    } else {
        newNode = malloc(sizeof(struct node));

        newNode->task = malloc(sizeof(struct task));
        newNode->task->burst = burst;
        newNode->task->name = name;
        newNode->task->priority = priority;

        if (!(current->next)) {
            if (((newNode->task->burst) > (current->task->burst)) || ((newNode->task->burst) == (current->task->burst))) {
                current->next = newNode;
                newNode->next = NULL;
            } else {
                newNode->next = current;
                head = newNode;
                current = newNode;
            }
        } else {
            while (1) {
                if ((newNode->task->burst < current->next->task->burst)) {
                    if (newNode->task->burst > current->task->burst) {
                        newNode->next = current->next;
                        current->next = newNode;
                        current = head;
                        break;
                    } else if (newNode->task->burst < current->task->burst) {
                        head = newNode;
                        newNode->next = current;
                        current = head;
                        break;
                    }
                } else if (newNode->task->burst == current->next->task->burst) {
                    current = current->next;
                    if (current->next == NULL) {
                        newNode->next = NULL;
                    } else if (newNode->task->burst == current->next->task->burst) {
                        current = current->next;
                        newNode->next = current->next;
                    } else {
                        newNode->next = current->next;
                    }
                    current->next = newNode;
                    current = head;
                    break;
                } else if ((newNode->task->burst) > (current->next->task->burst)) {
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

void schedule() {
    float turnaroundtime = 0;
    float ResponseTime = 0;
    float WaitTime = 0;
    int burst = 0;
    struct node *ref = head;
    while (ref != NULL) {
        num++;
        run(ref->task, ref->task->burst);
        burst += ref->task->burst;
        turnaroundtime += burst;
        if (ref->next != NULL) {
            ResponseTime += burst;
        }
        ref = ref->next;
    }
    WaitTime = turnaroundtime - burst;

    printf("The average turnaround time is : %f time units \n", (turnaroundtime) / num);
    printf("The average ResponseTime is : %f time units \n", (ResponseTime) / num);
    printf("The average WaitTime is : %f time units\n ", (WaitTime) / num);
}
