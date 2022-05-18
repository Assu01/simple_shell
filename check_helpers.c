#include "shell.h"

/**
 * exit_check - checks if user input is "exit" and, if so, exits the shell
 * @user_input: string to compare to "exit"
 * @NAME: name of program
 *
 * Return: 0 if not exit, -1 if exit has an invalid status attached
 */

int exit_check(char *user_input, char *NAME)
{
	int i, j, length, size, status;
	char *number;
	char *check = "exit";

	j = 0;
	length = _strlen(user_input);
	size = length - 5;
	status = 0;
	for (i = 0; i < 4; i++)
	{
		if (check[i] != user_input[i])
			return (0);
	}
	if (user_input[4] != '\n' && user_input[4] != ' ')
		return (0);

	if (length > 5)
	{
		number = malloc(sizeof(char) * size);
		for (i = 5; i < length - 1; i++)
		{
			if (user_input[i] >= '0' && user_input[i] <= '9')
			{
				number[j] = user_input[i];
				j++;
			}
			else
			{
				exit_error(NAME, user_input);
				free(number);
				exitcode = 2;
				return (-1);
			}
		}
		number[j] = '\0';
		status = _atoi(number);
		free(number);
	}
	free(user_input);
	exit(status);
}

/**
 * blank_check - checks if user input is just a return
 * @user_input: string to compare to "\n"
 *
 * Return: 1 if user_input is equal to '\n', 0 otherwise
 */

int blank_check(char *user_input)
{
	if (user_input[0] == '\n')
		return (1);

	return (0);
}

/**
 * path_check - checks if command contains path
 * @command: string to check for slash which denotes path
 *
 * Return: 0 if success, -1 if failure
 */

int path_check(char *command)
{
	if (command[0] == '/')
		return (0);

	return (-1);
}

/**
 * env_check - checks if command is env
 * @user_input: string to compare to 'env'
 *
 * Return: 1 if string is equal to 'env', otherwise 0
 */

int env_check(char *user_input)
{
	int i = 0;
	char *env = "env";

	if (_strlen(user_input) != 4)
		return (0);

	while (env[i] != '\0')
	{
		if (env[i] != user_input[i])
			return (0);
		i++;
	}
	return (1);
}
