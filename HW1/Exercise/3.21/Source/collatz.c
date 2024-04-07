#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void collatz_sequence(int n) {
    while (n != 1) {
        printf("%d ", n);
        if (n % 2 == 0)
            n = n / 2;
        else
            n = 3 * n + 1;
    }
    printf("%d\n", n);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please input: %s <positive_integer>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please provide a positive integer.\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        collatz_sequence(n);
        exit(0);
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to complete
    }

    return 0;
}

