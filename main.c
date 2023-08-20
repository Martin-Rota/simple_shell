#include "shell.h"

/**
 * main - Simple shell that executes commands
 *
 * Return: Always 0.
 */

int main(void)
{
	char input;

	while (1)
	{
		printf("Simple_Shell> ");

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\nExiting...\n");
				break;
			}
			else
			{
				perror("Error reading input");
				exit(EXIT_FAILURE);
			}
		}

		input[strcspn(input, "\n")] = '\0';

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
