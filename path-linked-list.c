#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct DirectoryNode {
    char *directory;
    struct DirectoryNode *next;
};

struct DirectoryNode *build_path_list() {
    struct DirectoryNode *head = NULL;
    struct DirectoryNode **tail = &head;

    const char *path_variable = _getenv("PATH");

    if (path_variable != NULL) {
        size_t path_copy_len = strlen(path_variable) + 1;
        char *path_copy = (char *)malloc(path_copy_len);
        if (!path_copy) {
            perror("Memory allocation error");
            return NULL;
        }
        strcpy(path_copy, path_variable);

        token = strtok(path_copy, ":");
        while (token != NULL) {
            struct DirectoryNode *new_node = (struct DirectoryNode *)malloc(sizeof(struct DirectoryNode));
            if (!new_node) {
                perror("Memory allocation error");
                free(path_copy);
                return NULL;
            }
            new_node->directory = strdup(token);
            new_node->next = NULL;

            *tail = new_node;
            tail = &((*tail)->next);
            token = strtok(NULL, ":");
        }

        free(path_copy);
    }

    return head;
}

void free_path_list(struct DirectoryNode *list) {
    while (list != NULL) {
        struct DirectoryNode *temp = list;
        list = list->next;
        free(temp->directory);
        free(temp);
    }
}

int main() {
    struct DirectoryNode *head = build_path_list();
    struct DirectoryNode *current = head;

    while (current != NULL) {
        printf("%s\n", current->directory);
        current = current->next;
    }

    free_path_list(head);

    return 0;
}

