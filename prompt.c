#include "shell.h"

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @bytes_read: characters read via get_line
 * @input: user's typed in command
 *
 */
void ctrl_D(int bytes_read, char *input)
{
	if (bytes_read == 0) /* handles Ctrl+D */
	{
		free(input); /* exit with newline if in shell */
		if (isatty(STDIN_FILENO))/* ctrl+d prints newline */
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * prompt - prompts user to enter command
 * @av: argument vector
 * @env: environmental variables
 */

void prompt(char **av,char **env)
{
	char *ptr, **args;
	ssize_t bytes_read = 0;
	pid_t pid;
	size_t input_size = 20;
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		ptr = malloc(sizeof(char) * input_size);
		bytes_read = getline(&ptr, &input_size, stdin);
		ctrl_D(bytes_read, ptr);

		if (bytes_read == -1)
		{
			free(ptr);
			exit(1);
		}
		if (*ptr != '\n')
		{
			args = _strtok(ptr);

			pid = fork();

			if (pid == -1)
			{
				perror("fork error");
				free(ptr);
				exit(1);
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
	}
	free(ptr);
}
