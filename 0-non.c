#include "main.h"
/**
* exec_non_interactive - execute non interactively
* @ar: executable file name
*/
void exec_non_interactive(char **ar)
{
	int status, j = 0, exit_status = 0, env_last_state = 0;
	int  cur_state = 0, cur_index = -2, add_case = 0;
	size_t count = 1;
	char *cmd;
	int index[1024];

	for (j = 0; j < 1024; j++)
		index[j] = -1;
	while (1)
	{
		cmd = _interline();
		execute_non(ar[0], cmd, &status, &exit_status, &env_last_state,
			&cur_state, &cur_index, &add_case, index, &count);
	}
	exit(0);
}
/**
* execute_non - execute non interactive
* @ar: filename
* @cmd: commands
* @status: child exit status
* @exit_status: exit status
* @env_last_state: last state of manupulaion of env var
* @cur_state: cur state of env var modification
* @cur_index: current index of modified env var
* @add_case: if any case where new env var was added
* @index: store modfied env var indexes
* @count: command count excuted till now
*/
void execute_non(char *ar, char *cmd, int *status, int *exit_status,
	int *env_last_state, int *cur_state, int *cur_index,
		int *add_case, int *index, size_t *count)
{
	char **commands = NULL, **argv, **commands_semi;
	char *abs_path;
	int k  = -1, j = -1;
	char sep[] = {'\n'};
	pid_t pid;

	if (cmd == NULL)
	{
		free_environ_exit(env_last_state, index, add_case);
		exit(0);
	}
	commands = (char **)_strtok(cmd, commands, sep);
	while (commands && commands[++k])
	{
		commands_semi = (char **)_strtok(commands[k], commands_semi, ";");
		while (commands_semi && commands_semi[++j])
		{
			argv = (char **)_strtok(commands_semi[j], argv, " ");
			if (argv && argv[0] && (_strcmp(argv[0], "exit") == 0))
				__exit_semi(commands_semi, commands, cmd, argv,
					env_last_state, index, add_case);
			if (init_exec(*count, ar, argv, exit_status,
				env_last_state, index, cur_state, cur_index, add_case, count, ar))
				continue;
			else
			{
				abs_path = get_absolute_path(argv[0]);
				pid = fork();
				if  (pid == 0)
					execve(abs_path, argv, environ);
				else
					exec_parent(NULL, status, abs_path, argv, exit_status);
			}
		}
		j = -1;
		(*count)++;
		 free_dblptr(commands_semi, NULL);
	}
	free_ptr(cmd);
	exit(0);
}
