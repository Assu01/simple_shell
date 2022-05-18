#include "shell.h"

/**
 * fork_wait_exec - executes commands by first forking a child process
 * then executing in that child while the parent process waits
 *
 * @commands: array of strings
 * commands[0] is command to execute
 * @env: array of environment variables
 * remaining strings are arguments to use with that command
 */

void fork_wait_exec(char **commands, char **path_array, char **env, char *NAME, char *user_input)
{
	pid_t pid;
	int status, exec_check;

	status = 0;
	pid = fork();

	if (pid == -1)
	{
		perror(NAME);
		_exit(1);
	}

	else if (pid == 0)
	{
		exec_check = execve(commands[0], commands, env);

		if (exec_check < 0)
		{
			exec_error(NAME, commands[0]);
			free_array(path_array);
			free_array(commands);
			free(user_input);
		}

		_exit(0);

	}

	wait(&status);
}
