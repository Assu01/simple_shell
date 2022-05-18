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

void fork_wait_exec(char **commands, char **env)
{
	pid_t pid;
	int status;

	status = 0;
	pid = fork();

	if (pid == -1)
	{
		perror("fork failure");
		_exit(1);
	}

	else if (pid == 0)
	{
		if ((execve(commands[0], commands, env)) < 0)
		{
			perror(commands[0]);
			_exit(1);
		}
		_exit(0);

	}

	wait(&status);
}
