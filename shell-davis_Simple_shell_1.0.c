#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 10  /* Maximum number of arguments*/

int main() {
    char *input = NULL;
    size_t len = 0;
    ssize_t read_len;
    int arg_count;
    pid_t pid;

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

        if (strcmp(input, "exit") == 0) {
            break;  /* Exit the shell*/
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            /* Child process */
            char *args[MAX_ARGS];  /* Array to store arguments*/
            args[0] = strtok(input, " ");  /* Tokenize the command*/
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

    free(input);
    return 0;
}

