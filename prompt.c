#include "shell.h"

/**
 * prompt - prompts user to enter command
 *
 * Return: Always 0.
 */

int prompt()
{
	char input[1024];

	while (1)
	{
		printf("Simple_Shell> ");

		ssize_t bytes_read = read(STDIN_FILENO, input, sizeof(input) - 1);

		if (bytes_read == -1)
		{
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}
		else if (bytes_read == 0)
		{
			printf("\nExiting...\n");
			break;
		}

		input[bytes_read - 1] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			printf("Exiting...\n");
			break;
		}

		pid_t pid = fork();

		if (pid == 0)
		{
			/* Child process */
			char *args[] = {input, NULL};

			if (execvp(input, args) == -1)
			{
				perror("command execution failed");
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

	return (0);
}
