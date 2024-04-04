#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please input: %s <command>\n", argv[0]);
        return 1;
    }

    int pipefd[2];
    struct timeval start, end;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) { // Child process
        close(pipefd[0]); // Close unused read end
        gettimeofday(&start, NULL);
        write(pipefd[1], &start, sizeof(start));
        close(pipefd[1]); // Close write end before exec
        execvp(argv[1], &argv[1]);
        perror("execvp"); // This will be printed only if execvp fails
        exit(1);
    } else { // Parent process
        close(pipefd[1]); // Close unused write end
        wait(NULL);
        gettimeofday(&end, NULL);
        struct timeval start;
        read(pipefd[0], &start, sizeof(start));
        close(pipefd[0]); // Close read end after read
        long elapsed_sec = end.tv_sec - start.tv_sec;
        long elapsed_usec = end.tv_usec - start.tv_usec;
        // Adjust microseconds if negative
	if (elapsed_usec < 0) {
	    elapsed_sec--;
	    elapsed_usec += 1000000; // 1 second = 1000000 microseconds
	}
        printf("Elapsed time: %ld.%06ld seconds\n", elapsed_sec, elapsed_usec);
    }

    return 0;
}
