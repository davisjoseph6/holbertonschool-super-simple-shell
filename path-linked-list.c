#include <stdio.h>
#include <stdlib.h>
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

struct DirectoryNode {
    char *directory;
    struct DirectoryNode *next;
};

struct DirectoryNode *build_path_list() {
    struct DirectoryNode *head = NULL;
    struct DirectoryNode **tail = &head;

    const char *path_variable = _getenv("PATH");

    if (path_variable != NULL) {
        char path_copy[strlen(path_variable) + 1];
        strcpy(path_copy, path_variable);

        char *token = strtok(path_copy, ":");
        while (token != NULL) {
            *tail = (struct DirectoryNode *)malloc(sizeof(struct DirectoryNode));
            (*tail)->directory = strdup(token);
            (*tail)->next = NULL;

            tail = &((*tail)->next);
            token = strtok(NULL, ":");
        }
    }

    return head;
}

int main() {
    struct DirectoryNode *head = build_path_list();
    struct DirectoryNode *current = head;

    while (current != NULL) {
        printf("%s\n", current->directory);
        current = current->next;
    }

    // Free memory
    while (head != NULL) {
        struct DirectoryNode *temp = head;
        head = head->next;
        free(temp->directory);
        free(temp);
    }

    return 0;
}

