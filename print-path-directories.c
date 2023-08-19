#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;
char *token;

char *_getenv(const char *name) {
    char **env = environ;
    size_t name_len = strlen(name);

    while (*env != NULL) {
        if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=') {
            return &((*env)[name_len + 1]);
        }
        env++;
    }

    return NULL;
}

void print_path_directories() {
    const char *path_variable = _getenv("PATH");

    if (path_variable != NULL) {
        char *path_copy = (char *)malloc(strlen(path_variable) + 1);
        if (path_copy == NULL) {
            perror("Memory allocation error");
            return;
        }
        strcpy(path_copy, path_variable);

        token = strtok(path_copy, ":");
        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, ":");
        }

        free(path_copy);
    } else {
        printf("PATH environment variable not found\n");
    }
}

int main() {
    print_path_directories();
    return 0;
}

