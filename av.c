#include <stdio.h>

int main(int ac, char **av)
{
    int i = 0;

    /* Using the ac parameter to suppress the unused parameter warning */
    printf("Number of arguments: %d\n", ac);

    while (av[i])
    {
        printf("%s ", av[i]);
        i++;
    }
    printf("\n");
    return 0;
}

