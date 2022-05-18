#include "shell.h"

/**
 * fork_wait_exec - executes commands by first forking a child process
 * then executing in that child while the parent process waits
 *
 * @commands: array of strings
 * commands[0] is command to execute
 * @path_array: array of directories in PATH
 * @env: array of environment variables
 * remaining strings are arguments to use with that command
 * @NAME: name of program
 * @user_input: input string
 */

void fork_wait_exec(char **commands, char **path_array, char **env,
		    char *NAME, char *user_input)
{
	pid_t pid;
	int status, exec_check;

	status = 0;
	pid = fork();

	if (pid == -1)
	{
		perror(NAME);
		exitcode = 1;
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
			exitcode = 126;
			_exit(126);
		}

		exitcode = 0;
		_exit(0);

	}

	exitcode = 0;
	wait(&status);
}
