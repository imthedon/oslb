#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else if (pid > 0) {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
    } else {
        // Fork failed
        printf("Fork failed\n");
    }

    return 0;
}

