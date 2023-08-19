#include <stdio.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name) {
    char **env = environ;
    size_t name_len = strlen(name);

    while (*env != NULL) {
        if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=') {
            return &((*env)[name_len + 1]); /* Return the value part */
        }
        env++;
    }

    return NULL; /* Environment variable not found */
}

int main() {
    const char *var_name = "PATH";
    char *var_value = _getenv(var_name);

    if (var_value != NULL) {
        printf("%s=%s\n", var_name, var_value);
    } else {
        printf("%s not found\n", var_name);
    }

    return 0;
}

