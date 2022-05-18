#include "main.h"
/**
* cd_home - go to home dir
* @exit_status: set exit status
* @env_last_state: sete or get last stat
* @index: all changed env vars
* @cur_state: set cur state
* @cur_index: set current index of env var modified
* @add_case: if any new var added
* @count: increase count of commands executed
* @ar: executable file name
* Return: 1 if success 2 if failed
*/
int cd_home(int *exit_status, int *env_last_state, int *index,
	int *cur_state, int *cur_index, int *add_case, size_t *count, char *ar)
{
	char *valid_home, *old_pwd, *pwd;
	int i;

		valid_home = _getenv("HOME");
		old_pwd = _getcwd();
		if (valid_home)
		{
			i = chdir(valid_home);
			if (i == -1)
			{
				_printf("%s: %d: cd: can't cd to %s\n", ar, (int)*count, valid_home);
				free(old_pwd);
				*exit_status = 2;
				return (2);
			}
			_setenv("OLDPWD", old_pwd, 1, env_last_state,
					index, cur_state, cur_index, add_case);
			pwd = _getcwd();
			_setenv("PWD", pwd, 1, env_last_state, index,
					cur_state, cur_index, add_case);
			free(pwd);
			free(old_pwd);
			*exit_status = 0;
			return (1);
		}
		_printf("%s: %d: cd: can't cd to %s\n",
				ar, (int)*count, valid_home);
		free(old_pwd);
		*exit_status = -1;
		return (2);
}
/**
* cd_prev - go to prevous dir
* @exit_status: set exit status
* @env_last_state: sete or get last stat
* @index: all changed env vars
* @cur_state: set cur state
* @cur_index: set current index of env var modified
* @add_case: if any new var added
* @count: increase count of commands executed
* @ar: executable file name
* Return: 1 if success 2 if failed
*/

int cd_prev(int *exit_status, int *env_last_state, int *index,
	int *cur_state, int *cur_index, int *add_case, size_t *count, char *ar)
{
	char *old_pwd, *pwd;
	int i;

		old_pwd = _getcwd();
		i = chdir(_getenv("OLDPWD"));
		if (i == -1)
		{
			_printf("%s: %d: cd: can't cd to %s\n",
					ar, (int)*count, _getenv("OLDPWD"));
			free(old_pwd);
			*exit_status = 2;
			return (2);
		}
		_setenv("OLDPWD", old_pwd, 1, env_last_state, index,
				cur_state, cur_index, add_case);
		pwd = _getcwd();
		_setenv("PWD", pwd, 1, env_last_state, index,
				cur_state, cur_index, add_case);
		_printf("%s\n", pwd);
		free(pwd);
		free(old_pwd);
		*exit_status = 0;
		return (1);
}
/**
* cd - change dir
* @argv: total arg vector
* @exit_status: set exit status
* @env_last_state: sete or get last stat
* @index: all changed env vars
* @cur_state: set cur state
* @cur_index: set current index of env var modified
* @add_case: if any new var added
* @count: increase count of commands executed
* @ar: executable file name
* Return: 1 if success 2 if failed
*/

int cd(char **argv, int *exit_status, int *env_last_state, int *index,
	int *cur_state, int *cur_index, int *add_case, size_t *count, char *ar)
{
	int i;
	char *old_pwd, *pwd;

	if (argv[1] == NULL)
		return (cd_home(exit_status, env_last_state, index,
			cur_state, cur_index, add_case, count, ar));
	if (_strcmp(argv[1], "-") == 0)
		return (cd_prev(exit_status, env_last_state, index,
			cur_state, cur_index, add_case, count, ar));
	old_pwd = _getcwd();
	i = chdir(argv[1]);
	if (i == -1)
	{
		_printf("%s: %d: cd: can't cd to %s\n",
				ar, (int)*count, argv[1]);
		free(old_pwd);
		*exit_status = 2;
		return (2);
	}
	_setenv("OLDPWD", old_pwd, 1, env_last_state, index,
			cur_state, cur_index, add_case);
	pwd = _getcwd();
	_setenv("PWD", pwd, 1, env_last_state, index, cur_state, cur_index, add_case);
	free(pwd);
	free(old_pwd);
	*exit_status = 0;
	return (1);
}
/**
* exec_builtin - execute builtin fucntion if any
* @argv: total arg vector
* @exit_status: set exit status
* @env_last_state: sete or get last stat
* @index: all changed env vars
* @cur_state: set cur state
* @cur_index: set current index of env var modified
* @add_case: if any new var added
* @count: increase count of commands executed
* @ar: executable file name
* Return: 1 always
*/


int exec_builtin(char **argv, int *exit_status,
	int *env_last_state, int *index, int *cur_state,
	int *cur_index, int *add_case, size_t *count, char *ar)
{
	if (argv && argv[0] && (_strcmp(argv[0], "cd") == 0))
		return (cd(argv, exit_status, env_last_state, index, cur_state,
				cur_index, add_case, count, ar));
	if (argv && argv[0] && (_strcmp(argv[0], "env") == 0))
		return (call_env(exit_status, count));

	if (argv && argv[0] && (_strcmp(argv[0], "setenv") == 0))
		return (call_setenv(argv, exit_status, env_last_state, index,
			cur_state, cur_index, add_case, count));
	if (argv && argv[0] && (_strcmp(argv[0], "getenv") == 0))
		return (call_getenv(argv, exit_status, count));
	if (argv && argv[0] && (_strcmp(argv[0], "echo") == 0) &&
		argv[1] && (argv[1][0] == '$'))
		return (echo(argv, exit_status, count));

	return (0);
}
/**
* init_exec - initial execution condition /executions
* @c:program execution counter
* @n: program name
* @argv: total arg vector
* @exit_status: set exit status
* @env_last_state: sete or get last stat
* @index: all changed env vars
* @cur_state: set cur state
* @cur_index: set current index of env var modified
* @add_case: if any new var added
* @count: increase count of commands executed
* @ar: executable file name
* Return: 1 if success 2 if failed
*/


int init_exec(size_t c, char *n, char **argv, int *exit_status,
	int *env_last_state, int *index, int *cur_state,
		int *cur_index, int *add_case, size_t *count, char *ar)
{
	char *abs_path;

	if (argv[0] == NULL)
	{
		*exit_status = 0;
		free_dblptr(argv, NULL);
		return (2);
	}
	if (exec_builtin(argv, exit_status, env_last_state,
		index, cur_state, cur_index, add_case, count, ar))
	{
		free_dblptr(argv, NULL);
		return (1);
	}
	abs_path = get_absolute_path(argv[0]);
	if (abs_path == NULL)
	{
		_printf("%s: %d: %s: not found\n", n, c, argv[0]);
		*exit_status = 127;
		free_dblptr(argv, NULL);
		return (1);
	}
	if (argv[0][0] != '/')
		free_ptr(abs_path);
	return (0);
}
