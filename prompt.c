#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *buffer = malloc(1024);
    size_t len = 1024;

    while (1)
    {
        printf("$ ");
        ssize_t bytesRead = getline(&buffer, &len, stdin);
        
        if (bytesRead == -1)
        {
            printf("\n"); // End-of-file or error occurred
            break;
        }

        printf("%s", buffer);
    }

    free(buffer); // Free allocated memory
    return 0;
}

