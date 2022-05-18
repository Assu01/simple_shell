#include "shell.h"

/**
 * get_path_count - counts number of directories in PATH
 * @path: PATH string
 *
 * Return: number of directories
 */

int get_path_count(char *path)
{
	int i, count;

	i = 0;
	count = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '=' || path[i] == ':')
			count++;
		i++;
	}

	return (count);
}

/**
 * get_path_array - creates an array of PATH directories
 * @env: user environment
 *
 * Return: array of strings
 */

char **get_path_array(char **env)
{
	unsigned int i, j, path_count;
	int compare;
	char *token, *mypath;
	char **path_array;

	compare = 0;
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		compare = strncmp(env[i], "PATH", 4);
		if (compare == 0)
		{
			mypath = _strdup(env[i]);
			path_count = get_path_count(mypath);
			path_array = malloc(sizeof(char *) * (path_count + 1));
			if (path_array == NULL)
				return (NULL);


			token = strtok(mypath, "=:");
			while (j < path_count)
			{
				if (token[0] != 'P')
				{
					path_array[j] = _strdup(token);
					j++;
				}
				token = strtok(NULL, "=:");
			}
		}
		i++;
	}

	path_array[path_count] = '\0';

	free(mypath);

	return (path_array);
}

/**
 * find_path - find the PATH of a command
 * @path_array: array of directories in PATH
 * @command: command to find path for
 *
 * Return: path of command, NULL if it fails
 */

char *find_path(char **path_array, char *command)
{
	int i, j, f_ok, dir_len, com_len, total_len;
	char *path;

	f_ok = 0;

	for (i = 0; path_array[i] != NULL; i++)
	{
		dir_len = _strlen(path_array[i]);
		com_len = _strlen(command);

		total_len = dir_len + com_len;

		path = malloc(sizeof(char) * (total_len + 2));

		j = 0;
		while (j < dir_len)
		{
			path[j] = path_array[i][j];
			j++;
		}
		path[j] = '/';

		j = 0;
		while (j < com_len)
		{
			path[dir_len + j + 1] = command[j];
			j++;
		}
		path[total_len + 1] = '\0';

		f_ok = access(path, F_OK);

		if (f_ok == 0)
			return (path);

		else
			free(path);
	}

	return (NULL);
}

/**
 * print_env - print environment variables
 * @env: array of environment variables
 */

void print_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
