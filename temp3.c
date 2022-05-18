#include "main.h"
/**
* __exit -exit process with some exit status
* @commands: commands separated by semicolon or special char
* @cmd: associated command pointer to free
* @argv: argv to be freed
* @env_last_state: enviromental variable change last state
* @index: all index of env variables changed so far
* @add_case: if any time new env var was add or not
*/
void __exit(char **commands, char *cmd, char **argv, int *env_last_state,
		int *index, int *add_case)
{
	int stat;

	if (argv[1])
		stat = _atoi(argv[1]);
	else
		stat = 0;
	free_dblptr(argv, NULL);
	free_dblptr(commands, cmd);
	free_environ_exit(env_last_state, index, add_case);
	exit(stat);
}


/**
* get_absolute_path -get absolute path give file name
* @name: file name to be searched
* Return: on success absolute path on fail  NULL
*/
char *get_absolute_path(char *name)
{
	char *path_cwd, *path_in_path;

	if (name[0]  == '/')
	{
		return (name);
	}
	path_cwd = check_in_cwd(name);
	if (path_cwd)
		return (path_cwd);
	path_in_path = check_in_path(name);
	if (path_in_path)
		return (path_in_path);
	return (NULL);
}
/**
 * print_env - print environmental variables
 * @env: env var array
 */
void print_env(char **env)
{
	size_t i = 0;

	while (env[i])
	{
		_printf("%s\n", environ[i]);
		i++;
	}
}
/**
* call_setenv - function that set env var
* @argv: total arg vector
* @exit_status: set exit status
* @env_last_state: sete or get last stat
* @index: all changed env vars
* @cur_state: set cur state
* @cur_index: set current index of env var modified
* @add_case: if any new var added
* @count: increase count of commands executed
* Return: 1 always
*/


int call_setenv(char **argv, int *exit_status,
	int *env_last_state, int *index, int *cur_state,
	int *cur_index, int *add_case, __attribute__((unused))size_t *count)
{
	if (argv[1] && argv[2])
		_setenv(argv[1], argv[2], 1, env_last_state,
			index, cur_state, cur_index, add_case);
	else
	{
		_printf("usage: setenv var value\n");
		*exit_status = 0;
	}
	*exit_status = 0;
	return (1);
}
/**
 * echo - variable sbstitution function
 * @argv: command line args
 * @exit_status: set exit status
 * @count: set command count
 * Return: 1 always
 */
int echo(char **argv, int *exit_status, __attribute__((unused))size_t *count)
{
	if ((_strcmp(argv[1], "$$") == 0))
	{
		_printf("%d\n", getppid());
		*exit_status = 0;
		return (1);
	}
	if (_strcmp(argv[1], "$?") == 0)
	{
		_printf("%d\n", *exit_status);
		*exit_status = 0;
		return (1);
	}
	if (_getenv(&(argv[1][1])))
		_printf("%s\n", _getenv(&(argv[1][1])));
	else
		_printf("%s: not found\n", _getenv(&(argv[1][1])));
	*exit_status = 0;
	return (1);
}
