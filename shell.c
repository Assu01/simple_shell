#include "shell.h"

/**
 * main - a simple shell program written in C
 * @argc: number of arguments
 * @argv: array of arguments
 * @env: array of environment variables
 *
 * Return: 0 always (but program may exit early)
 */

int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	char *user_input;
	size_t nbytes = 0;
	ssize_t bytes_read = 0;
	char **commands, **path_array;
	char *NAME = argv[0];
	int atty_is = isatty(0);

	user_input = NULL;
	commands = NULL;
	path_array = NULL;

	while (1)
	{
		if (atty_is)
			write(STDOUT_FILENO, "hella_shell$ ", 13);

		bytes_read = getline(&user_input, &nbytes, stdin);
		if (bytes_read == -1)
			exit(2);

		if (bytes_read == 5)
			exit_check(user_input);

		if (blank_check(user_input) == 1)
			continue;

		if (env_check(user_input) == 1)
		{
			print_env(env);
			continue;
		}

		path_array = get_path_array(env);
		commands = parse_input(user_input, path_array, NAME, atty_is);

		if (commands != NULL)
		{
			fork_wait_exec(commands, path_array, env, NAME, user_input);
			free_array(commands);
			free_array(path_array);
		}
	}

	return (0);
}
