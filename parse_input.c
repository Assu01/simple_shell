#include "shell.h"

/**
 * parse_input - parsers user_input to create an array of strings
 * @user_input: string to tokenize
 * @path_array: array of directories in PATH
 * @NAME: name of program
 * @atty: denotes interactive or non-interactive mode
 *
 * Return: an array of arguments
 */

char **parse_input(char *user_input, char **path_array, char *NAME, int atty)
{
	char **commands;
	char *token, *dir_path;
	int args, i, start;

	dir_path = NULL;
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
	if (commands == NULL)
	{
		free_array(path_array);
		return (NULL);
	}
	token = strtok(user_input, "\n ");

	if (path_check(token) == -1)
	{
		dir_path = find_path(path_array, token);

		if (dir_path == NULL)
		{
			free(commands);
			free_array(path_array);
			command_error(NAME, token, atty);
			return (NULL);
		}
		else if (_strcmp("no_access", dir_path) == 0)
		{
			free(commands);
			free(path_array);
			access_error(NAME, token);
			return (NULL);
		}

		else
		{
			commands[0] = _strdup(dir_path);
			free(dir_path);
		}
	}

	else
		commands[0] = _strdup(token);

	for (i = 1; i < args; i++)
	{
		token = strtok(0, "\n ");
		commands[i] = _strdup(token);
	}

	commands[i] = NULL;

	return (commands);
}
