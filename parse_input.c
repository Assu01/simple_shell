#include "shell.h"

/**
 * parse_input - parsers user_input to create an array of strings
 * @user_input: string to tokenize
 * @path_array: array of directories in PATH
 *
 * Return: an array of arguments
 */

char **parse_input(char *user_input, char **path_array, char *NAME)
{
	char **commands;
	char *token, *dir_path;
	int args, i, start;

	args = 1;
	i = 0;
	start = 0;
	while (user_input[i] != '\0' && user_input[i] != '\n')
	{
		if (user_input[i] != ' ')
			start = 1;

		if (user_input[i] == ' ' && user_input[i + 1] != ' '
		    && user_input[i + 1] != '\n' && start == 1)
			args++;

		i++;
	}

	commands = malloc(sizeof(char *) * (args + 1));
	token = strtok(user_input, "\n ");

	if (path_check(token) == -1)
	{
		dir_path = find_path(path_array, token);
		if (dir_path != NULL)
		{
			commands[0] = _strdup(dir_path);
			free(dir_path);
		}
		else
		{
			perror(NAME);
			free(dir_path);
			free(commands);
			return (NULL);
		}
	}
	else
		commands[0] = _strdup(token);

	for (i = 1; i < args; i++)
	{
		token = strtok(NULL, "\n ");
		commands[i] = _strdup(token);
	}
	commands[i] = NULL;

	return (commands);
}
