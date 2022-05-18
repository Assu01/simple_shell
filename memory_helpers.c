#include "shell.h"

/**
 * free_commands - free an array of strings
 * @commands: array to free
 */

void free_commands(char **commands)
{

/*
	int i;

	for (i = 0; commands[i] != NULL; i++)
	{
		printf("about to free: %s\n", commands[i]);
		free(commands[i]);
	}
*/

	free(commands);
}
