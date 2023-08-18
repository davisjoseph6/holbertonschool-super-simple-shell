#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

void execute_command(char *command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        // Child process
        char *args[] = {command, NULL};
        execve(command, args, NULL);
        perror("execve");
        _exit(1);
    } else {
        // Parent process
        wait(NULL);
    }
}

int main() {
    char *input = NULL;
    size_t len = 0;

    while (1) {
        printf("#cisfun$ ");
        ssize_t read_len = getline(&input, &len, stdin);

        if (read_len == -1) {
            if (feof(stdin)) {
                printf("\n");
                break;
            } else {
                perror("getline");
                exit(1);
            }
        }

        if (input[read_len - 1] == '\n') {
            input[read_len - 1] = '\0'; // Remove the newline character
        }

        execute_command(input);
    }

    free(input);
    return 0;
}

