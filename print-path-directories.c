#include <stdio.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name) {
    char **env = environ;
    size_t name_len = strlen(name);

    while (*env != NULL) {
        if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=') {
            return &((*env)[name_len + 1]); // Return the value part
        }
        env++;
    }

    return NULL; // Environment variable not found
}

void print_path_directories() {
    const char *path_variable = _getenv("PATH");

    if (path_variable != NULL) {
        char path_copy[strlen(path_variable) + 1];
        strcpy(path_copy, path_variable);

        char *token = strtok(path_copy, ":");
        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, ":");
        }
    } else {
        printf("PATH environment variable not found\n");
    }
}

int main() {
    print_path_directories();
    return 0;
}

