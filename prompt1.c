#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *buffer = NULL;  // Initialize the buffer pointer
    size_t len = 0;       // Initialize the buffer size

    while (1) {
        printf("$ ");
        ssize_t read = getline(&buffer, &len, stdin);  // Use ssize_t for error handling
        if (read == -1) {
            if (feof(stdin)) {
                // End of file (Ctrl+D) encountered, break out of the loop
                printf("\n");
                break;
            } else {
                // Error occurred while reading input, handle it
                perror("getline");
                free(buffer);  // Free allocated memory before exiting
                return 1;
            }
        }

        printf("%s", buffer);
    }

    // Free allocated memory before exiting
    free(buffer);

    return 0;
}

