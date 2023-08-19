#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("$ ");
        read = getline(&buffer, &len, stdin);
        if (read == -1) {
            if (feof(stdin)) {
                printf("\n");
                break;
            } else {
                perror("getline");
                free(buffer);
                return 1;
            }
        }

        printf("%s", buffer);
    }

    free(buffer);
    return 0;
}

