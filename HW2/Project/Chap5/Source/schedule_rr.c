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
struct node *monitor = NULL;
int num = 0;

void add(char *name, int priority, int burst) {
    num++;
    if (head == NULL) {
        head = malloc(sizeof(struct node));
        last = malloc(sizeof(struct node));

        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->burst = burst;
        head->task->priority = priority;
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

void schedule() {
    struct node *current = head;
    struct node *ref = head;
    monitor = malloc(sizeof(struct node));
    monitor = head;
    int newburst = 0;
    int totburst = 0;
    float turnaroundtime = 0;
    float responseTime = 0;
    float waitTime = 0;
    int check = 1;

    while (ref != NULL) {
        if (ref->task->burst >= 10) {
            newburst = ref->task->burst - 10;

            if (current != head) {
                while (monitor != current) {
                    if (strcmp(current->task->name, monitor->task->name) == 0) {
                        check = 0;
                        break;
                    }
                    monitor = monitor->next;
                }
                monitor = head;
            }

            if (ref->task->burst > 10 && ref != head) {
                if (ref->next != NULL) {
                    if (check == 1) {
                        responseTime += totburst;
                    }
                }
            }

            if (ref->task->burst == 10) {
                if (check == 1) {
                    responseTime += totburst;
                }
            }

            totburst += 10;

            if (ref->task->burst == 10) {
                turnaroundtime += totburst;
            }

            ref->task->burst = 10;
            run(ref->task, 10);
        } else if (ref->task->burst < 10) {
            newburst = 0;
            if (check == 1) {
                responseTime += totburst;
            }
            totburst += ref->task->burst;
            turnaroundtime += totburst;
            run(ref->task, ref->task->burst);
        }

        while (1) {
            if (current->next != NULL) {
                current = current->next;
                if (current->next == NULL) {
                    if (newburst != 0) {
                        struct node *newNode = malloc(sizeof(struct node));
                        newNode->task = malloc(sizeof(struct task));
                        newNode->task->name = ref->task->name;
                        newNode->task->burst = newburst;
                        newNode->task->priority = ref->task->priority;
                        ref = ref->next;
                        current->next = newNode;
                        newNode->next = NULL;
                        current = ref;
                        break;
                    } else if (newburst == 0) {
                        ref = ref->next;
                        current = ref;
                        break;
                    }
                }
            } else {
                if (newburst != 0) {
                    struct node *new = malloc(sizeof(struct node));
                    new->task = malloc(sizeof(struct task));
                    new->task->name = ref->task->name;
                    new->task->priority = ref->task->priority;
                    new->task->burst = newburst;
                    ref->next = new;
                    ref = ref->next;
                    new->next = NULL;
                    current = new;
                } else {
                    ref = ref->next;
                }
                break;
            }
        }
    }

    waitTime = turnaroundtime - totburst;
    printf("The average turnaround time is : %f time units \n", turnaroundtime / num);
    printf("The average response time is : %f time units \n", responseTime / num);
    printf("The average Wait time is : %f time units \n", waitTime / num);
}
