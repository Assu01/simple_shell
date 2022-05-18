#include "main.h"
/**
* main - entry point to program
* @argc: arg counts
* @ar: argument vectors
* Return: 0 always
*/
int main(int __attribute__((unused)) argc, char **ar)
{
	int status, j = 0, exit_status = 0, env_last_state = 0;
	int  cur_state = 0, cur_index = -2, add_case = 0;
	size_t count = 1;
	char *cmd;
	char prompt[] = {'$', ' '};
	int index[1024];

	for (j = 0; j < 1024; j++)
		index[j] = -1;
	if (!isatty(fileno(stdin)))
		exec_non_interactive(ar);
	if (ar[1])
		exec_file_non_interactive(ar);
	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		fflush(stdout);
		cmd = _readline();
		execute(ar[0], cmd, &status, &exit_status, &env_last_state,
			&cur_state, &cur_index, &add_case, index, &count);

	}

	return (0);
}
/**
* execute - execute interactive
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

void execute(char *ar, char *cmd, int *status, int *exit_status,
	int *env_last_state, int *cur_state, int *cur_index,
		int *add_case, int *index, size_t *count)
{
	char **commands = NULL, **argv;
	char *abs_path;
	int k  =  0;

	pid_t pid;

		if (cmd == NULL)
		{
			free_environ_exit(env_last_state, index, add_case);
			exit(0);
		}
		commands = (char **)_strtok(cmd, commands, ";");
		while (commands && commands[k])
		{

			argv = (char **)_strtok(commands[k], argv, " ");
			if (argv && argv[0] && (_strcmp(argv[0], "exit") == 0))
				__exit(commands, cmd, argv, env_last_state, index, add_case);
			if (init_exec(*count, ar, argv, exit_status,
				env_last_state, index, cur_state, cur_index, add_case, count, ar))
			{
				k++;
				continue;
			}
			else
			{
				abs_path = get_absolute_path(argv[0]);
				pid = fork();
				if  (pid == 0)
					execve(abs_path, argv, environ);
				else if (pid > 0)
					exec_parent(NULL, status, abs_path, argv, exit_status);
			}
			k++;
		}
		(*count)++;
		free_dblptr(commands, cmd);
}
/**
* exec_parent - task performed by parent process
* @cmd: commandline text
* @st: status pointer
* @a_path: absolute path string
* @av: command line arguments
* @ex_st: exist status pointer
*/
void exec_parent(char *cmd, int *st, char *a_path, char **av, int *ex_st)
{
	wait(st);
	*ex_st = WEXITSTATUS(*st);
	if (av[0][0] != '/')
		free_ptr(a_path);
	free_dblptr(av, cmd);
}
