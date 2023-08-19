#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 1024

void find_executable(const char *filename, const char *path) {
    char path_copy[MAX_PATH_LENGTH];
    char *token;

    strncpy(path_copy, path, sizeof(path_copy));
    token = strtok(path_copy, ":");
    
    while (token != NULL) {
        char full_path[MAX_PATH_LENGTH];
        
        snprintf(full_path, sizeof(full_path), "%s/%s", token, filename);
        
        if (access(full_path, X_OK) == 0) {
            printf("%s\n", full_path);
            return;
        }
        
        token = strtok(NULL, ":");
    }
    
    printf("%s not found\n", filename);
}

int main(int argc, char **argv) {
    int i;
    char *path;

    if (argc < 2) {
        printf("Usage: %s filename ...\n", argv[0]);
        return 1;
    }

    path = getenv("PATH");
    if (path == NULL) {
        printf("Could not retrieve PATH environment variable\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        find_executable(argv[i], path);
    }

    return 0;
}

