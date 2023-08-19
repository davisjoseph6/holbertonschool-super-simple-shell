#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *path = getenv("PATH");
    char *path_copy;
    char *token;
    int i;

    if (path == NULL) {
        fprintf(stderr, "Could not retrieve PATH environment variable.\n");
        return 1;
    }

    path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    token = strtok(path_copy, ":");
    while (token != NULL) {
        for (i = 1; i < argc; i++) {
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s/%s", token, argv[i]);

            if (access(file_path, F_OK) == 0) {
                printf("%s\n", file_path);
            }
        }
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return 0;
}

