#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 *main-prototype
 *Return: 0
 */
int main(void)
{
	char *buffer = malloc(1024);
	size_t len = 1024;
	char *token;
	ssize_t bytesRead; 

	while (1)
	{
		printf("$ ");
		bytesRead = getline(&buffer, &len, stdin);
				
		printf("buffer getline: %s", buffer);
	
		token = strtok(buffer, " ");
		while (token)
		{
			printf("buffer strtok: %s\n", token);
			token = strtok(NULL, " ");
		}
		
		if (bytesRead == -1)
        	{	
            		printf("\n"); 
            		break;
        	}
	}
	return (0);
}
