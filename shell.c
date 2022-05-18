#include "shell.h"

int exitcode = 0;
int errorcount = 0;

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
	char *user_input = NULL;
	char **commands = NULL;
	char **path_array = NULL;
	size_t nbytes = 0;
	ssize_t bytes_read = 0;
	char *NAME = argv[0];
	int atty_is = isatty(0);
	char *filename = "splash_screen.txt";
	FILE *fptr = NULL;

	signal(SIGINT, SIG_IGN);

	// display splash screen
	if((fptr = fopen(filename,"r")) == NULL)
	{
		fprintf(stderr,"error opening %s\n",filename);
		return 1;
	}
	display_splash_screen(fptr);
	fclose(fptr);

	while (1)
	{
		errorcount++;
		if (atty_is)
			write(STDOUT_FILENO, "hella_shell$ ", 13);
		bytes_read = getline(&user_input, &nbytes, stdin);
		if (bytes_read == -1)
		{
			free(user_input);
			exit(exitcode);
		}
		if (exit_check(user_input, NAME) == -1)
			continue;
		if (blank_check(user_input) == 1)
			continue;
		if (env_check(user_input) == 1)
		{
			print_env(env);
			continue;
		}
		path_array = get_path_array(env);
		commands = parse_input(user_input, path_array, NAME);
		if (commands != NULL)
		{
			fork_wait_exec(commands, path_array, env, NAME, user_input);
			free_array(commands);
			free_array(path_array);
		}
	}
	return (0);
}
