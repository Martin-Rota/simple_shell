#include "shell.h"

/**
 * prompt - prompts user to enter command
 * @av: argument vector
 * @env: environmental variables
 * Return: 0.
 */

int prompt(char **av,char **env)
{
	char *input = NULL;
	ssize_t bytes_read;
	pid_t pid;
	size_t input_size = 0;

	while (1)
	{
		printf("MySimple_shell$ ");
		fflush(stdout);

		bytes_read = getline(&input, &input_size, stdin);

		if (bytes_read == -1)
		{
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}

		if (input[bytes_read - 1] == '\n')
		{
			input[bytes_read - 1] = '\0';
		}
		
		pid = fork();

		if (pid == 0)
		{
			/* Child process */
			char *args[2];

			args[0] = input;
			args[1] = NULL;

			if (execve(args[0], args, env) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			/* Parent process */
			int status;

			if (wait(&status) == -1)
			{
				perror("wait");
			}
		}
		else
		{
			perror("error creating child process");
		}
	}

	free(input);
	return (0);
}
