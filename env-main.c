#include <stdio.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(void)
{
    unsigned int i;
    extern char **environ;

    i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
    return 0;
}

