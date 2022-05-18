#include "shell.h"

/**
 * exit_check - checks if user input is "exit" and, if so, exits the shell
 * @user_input: string to compare to "exit"
 */

void exit_check(char *user_input)
{
	int i;
	char *check = "exit";

	for (i = 0; check[i] != '\0'; i++)
	{
		if (check[i] != user_input[i])
			return;
	}

	free(user_input);
	exit(0);
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
