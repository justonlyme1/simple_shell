#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[1024];

	while (1)
	{
		display_prompt();

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		input[strlen(input) - 1] = '\0';

		if (strlen(input) == 0)
		{
			continue;
		}

		execute_command(input);
	}

	return (0);
}
