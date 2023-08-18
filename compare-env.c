#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[], char *env[]) {
    printf("Address of env (parameter): %p\n", (void *)env);
    printf("Address of environ (global): %p\n", (void *)environ);

    if (env == environ) {
        printf("The addresses are the same.\n");
    } else {
        printf("The addresses are different.\n");
    }

    return 0;
}

