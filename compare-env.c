#include <stdio.h>

extern char **environ;

int main(void) {
    printf("Address of env (parameter): %p\n", (void *)environ);
    printf("Address of environ (global): %p\n", (void *)environ);

    if (environ == NULL) {
        printf("The environment variable is not available.\n");
    } else if (environ[0] == NULL) {
        printf("The environment variable is empty.\n");
    } else {
        printf("The environment variable is not empty.\n");
    }

    return 0;
}

