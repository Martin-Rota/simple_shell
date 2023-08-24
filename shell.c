#include "shell.h"

/**
 * main - creates a simple shell
 * @ac: argument count
 * @av: argument vectors
 * @env: environmental variables
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	(void)env;
	(void)av;

	if (ac == 1)
		prompt();

	return (0);
}
