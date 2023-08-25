#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void prompt(char **av,char **env);
int main(int ac, char **av, char **env);
void ctrl_D(int bytes_read, char *input);
int strtok_args(char *input, char **args);

#endif
