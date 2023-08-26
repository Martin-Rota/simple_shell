#include "shell.h"

/**
 * _strtok - Tokenizes a string into an array of strings
 * @str: The input string to be tokenized
 * 
 * Return: Array of strings
 */
char **_strtok(char *str)
{
	char *token, **args;
	int i = 0, j = 0;

	args = malloc(8 * sizeof(char *));
	if (args == NULL)
	{
		exit(1);
	}
	token = strtok(str, " ");
	while (token != NULL)
	{
		while (token[j])
		{
			if (token[j] == '\n')
				token[j] = '\0';
			j++;
		}
		args[i] = token;
		i++;
		j = 0;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}
