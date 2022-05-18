#include "main.h"
/**
* exec_file_non_interactive - execute non interactively
* @ar: executable file name
*/
void exec_file_non_interactive(char **ar)
{
	int status, j = 0, exit_status = 0, env_last_state = 0;
	int  cur_state = 0, cur_index = -2, add_case = 0;
	size_t count = 0;
	char *cmd;
	char *abs_path;
	int index[1024];

	for (j = 0; j < 1024; j++)
		index[j] = -1;
	if (ar[1][0] == '/')
		abs_path = ar[1];
	else
		abs_path = get_path_in_cwd(ar[1]);
	if (access(abs_path, R_OK) != 0)
	{
		write(STDERR_FILENO, ar[0], _strlen(ar[0]));
		_putchar(':');
		_putchar(' ');
		print_num((ssize_t)count);
		_putchar(':');
		_putchar(' ');
		write(STDOUT_FILENO, "Can't open ", 12);
		write(STDOUT_FILENO, ar[1], _strlen(ar[1]));
		_putchar('\n');
		if (ar[1][0] != '/')
			free_ptr(abs_path);
		exit(-1);
	}
	count++;
	cmd = _readFromFile(abs_path);
	if (ar[1][0] != '/')
		free_ptr(abs_path);
	execute_non(ar[1], cmd, &status, &exit_status, &env_last_state,
		&cur_state, &cur_index, &add_case, index, &count);
	exit(0);
}
