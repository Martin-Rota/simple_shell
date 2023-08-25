#include "shell.h"

/**
 * prompt - prompts user to enter command
 * @av: argument vector
 * @env: environmental variables
 * Return: 0.
 */

int prompt(char **av,char **env)
{
	char *input = NULL, *args[2];
	ssize_t bytes_read;
	pid_t pid;
	size_t input_size = 0;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		bytes_read = getline(&input, &input_size, stdin);

		if (bytes_read == -1)
		{
			free(input);
			exit(EXIT_FAILURE);
		}

		if (input[bytes_read - 1] == '\n')
		{
			input[bytes_read - 1] = '\0';
		}

		pid = fork();
		args[0] = input;
		args[1] = NULL;

		if (pid == -1)
		{
			perror("fork error");
			free(input);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (execve(args[0], args, env) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
			}
		}

		else
			wait(&status);
	}
	return (0);
}
