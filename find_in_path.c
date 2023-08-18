#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
        return 1;
    }

    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "Could not retrieve PATH environment variable.\n");
        return 1;
    }

    char *path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    char *token = strtok(path_copy, ":");
    while (token != NULL) {
        for (int i = 1; i < argc; i++) {
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

