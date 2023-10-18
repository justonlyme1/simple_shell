#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void display_prompt() {
	printf("simple_shell> ");
}
/**
 * execute_path - Execute a command found in the PATH.
 * @path: The PATH environment variable.
 * @args: An array of command arguments.
 * Return: 1 if there was an error, 0 otherwise.
 */
int execute_path(char *path, char *args[])
{
	char path_copy[1024];
	char *path_token;
	char command_path[1024];
	pid_t pid;
	int status;

	strncpy(path_copy, path, sizeof(path_copy));
	path_copy[sizeof(path_copy) - 1] = '\0';

	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);

		if (access(command_path, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execv(command_path, args);
				perror("Error executing command");
				exit(1);
			}
			else if (pid < 0)
			{
				perror("Error forking process");
				return (1);
			}
			else
			{
				waitpid(pid, &status, 0);
			}
		}

		path_token = strtok(NULL, ":");
	}

	printf("Command not found: %s\n", args[0]);
	return (1);
}

/**
 * execute_command - Execute a command in the shell.
 * @command_with_args: The command with arguments.
 * Return: 1 if there was an error, 0 otherwise.
 */
int execute_command(char *command_with_args)
{
	char *command = strtok(command_with_args, " ");
	char *args[1024];
	int i = 0;
	char *path = getenv("PATH");

	while (command != NULL)
	{
		args[i] = command;
		i++;
		command = strtok(NULL, " ");
	}
	args[i] = NULL;

	if (path == NULL)
	{
		perror("Error getting PATH");
		return (1);
	}

	return (execute_path(path, args));
}
