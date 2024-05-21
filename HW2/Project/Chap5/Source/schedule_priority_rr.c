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
struct node *current = NULL;

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
    current = head;
    struct node *ref = head;
    struct node *beginning = malloc(sizeof(struct node));
    int newBurst = 0;

    while (ref != NULL) {
        if (ref->next == NULL) {
            run(ref->task, ref->task->burst);
            break;
        } else {
            if ((ref->task->priority != ref->next->task->priority)) {
                run(ref->task, ref->task->burst);
                ref = ref->next;
            } else {
                if (ref->next != NULL) {
                    if ((ref->task->priority == ref->next->task->priority)) {
                        current = ref;
                        while (current->next != NULL) {
                            current = current->next;
                            if (current->task->priority != current->next->task->priority) {
                                beginning = current->next;
                                current->next = NULL;
                                current = ref;
                                break;
                            }
                        }

                        while (ref != NULL) {
                            if (ref->task->burst >= 10) {
                                newBurst = ref->task->burst - 10;
                                ref->task->burst = 10;
                                run(ref->task, 10);
                            } else if (ref->task->burst < 10) {
                                newBurst = 0;
                                run(ref->task, ref->task->burst);
                            }

                            while (1) {
                                if (current->next != NULL) {
                                    current = current->next;
                                    if (current->next == NULL) {
                                        if (newBurst != 0) {
                                            struct node *newNode = malloc(sizeof(struct node));
                                            newNode->task = malloc(sizeof(struct task));
                                            newNode->task->name = ref->task->name;
                                            newNode->task->burst = newBurst;
                                            newNode->task->priority = ref->task->priority;
                                            ref = ref->next;
                                            current->next = newNode;
                                            newNode->next = NULL;
                                            current = ref;
                                            break;
                                        } else if (newBurst == 0) {
                                            ref = ref->next;
                                            current = ref;
                                            break;
                                        }
                                    }
                                } else {
                                    ref = ref->next;
                                    current = beginning;
                                    break;
                                }
                            }
                        }
                        ref = beginning;
                    }
                }
            }
        }
    }
}
