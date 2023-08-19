#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *buffer = (char *)malloc(1024);
    size_t len = 1024;

    while (1) {
        ssize_t bytesRead;
        
        printf("$ ");
        bytesRead = getline(&buffer, &len, stdin);

        if (bytesRead == -1) {
            printf("\n");
            break;
        }

        printf("%s", buffer);
    }

    free(buffer);
    return 0;
}

