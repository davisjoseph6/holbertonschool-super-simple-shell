#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 10  /* Maximum number of arguments*/

void execute_command(char *command) {
    pid_t pid = fork();
    int arg_count;

    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        /* Child process */
        char *args[MAX_ARGS];  /* Array to store arguments*/
        args[0] = strtok(command, " ");  /* Tokenize the command*/
        arg_count = 1;

        while (arg_count < MAX_ARGS - 1) {
            args[arg_count] = strtok(NULL, " ");  /* Tokenize arguments*/
            if (args[arg_count] == NULL) {
                break;  /* No more arguments*/
            }
            arg_count++;
        }
        args[arg_count] = NULL;  /* Last argument must be NULL*/

        /* Execute command with arguments*/
        execvp(args[0], args);
        perror(args[0]);
        _exit(1);
    } else {
        /* Parent process */
        wait(NULL);
    }
}

int main() {
    char *input = NULL;
    size_t len = 0;
    ssize_t read_len;

    while (1) {
        printf(":) ");
        read_len = getline(&input, &len, stdin);

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
            input[read_len - 1] = '\0'; /* Remove the newline character */
        }

        execute_command(input);
    }

    free(input);
    return 0;
}

