#include "main.h"
/**
* __exit -exit process with some exit status
* @commands: commands separated by semicolon or special char
* @commands_semi: commands separated by semicolon or special char
* @cmd: associated command pointer to free
* @argv: argv to be freed
* @env_last_state: enviromental variable change last state
* @index: all index of env variables changed so far
* @add_case: if any time new env var was add or not
*/
void __exit_semi(char **commands_semi, char **commands, char *cmd, char **argv,
	int *env_last_state, int *index, int *add_case)
{
	int stat;

	if (argv[1])
		stat = _atoi(argv[1]);
	else
		stat = 0;
	free_dblptr(argv, NULL);
	free_dblptr(commands, cmd);
	free_dblptr(commands_semi, NULL);
	free_environ_exit(env_last_state, index, add_case);
	exit(stat);
}
/**
* call_getenv - helper function to peroform getenv command
* @argv: args vector
* @exit_status: exist status of current command
* @count: number of commands performed till now -> pointer
* Return: 1 always
*/
int call_getenv(char **argv, int *exit_status,
		__attribute__((unused))size_t *count)
{
		if (argv[1])
		{
			if (_getenv(argv[1]))
				_printf("%s\n", _getenv(argv[1]));
			else
				_printf("(nill)\n");
		}
		else
			_printf("Usage: getenv varname\n");
		*exit_status = 0;
		return (1);
}
/**
* call_env - helper function to execute env built in call
* @exit_status: exit status to be set
* @count: number of commands performed till now
* Return: 1 always
*/
int call_env(int *exit_status, __attribute__((unused))size_t *count)
{
		print_env(environ);
		*exit_status = 0;
		return (1);
}
/**
* free_environ_exit - free any malloc for environmental var at exit
* @env_last_state: last state of change in env vars
* @index: list of all env vars changed till now exit
* @add_case: if any in time new var was added or not
*/
void free_environ_exit(int *env_last_state, int *index, int *add_case)
{
	size_t j = 0;

	if (*add_case == 1)
	{
		while (environ[j])
		{
			if (environ[j])
				free(environ[j]);
			j++;
		}
		if (environ)
			free(environ);
	}
	else if (*add_case == 0 && *env_last_state == 1)
	{
		j = 0;
		while (index[j] != -1)
		{
			if (environ[index[j]])
			{
				free(environ[index[j]]);
			}
			j++;
		}
	}
}
/**
* free_environ - free env var malloc at any time when set / unset
* @old_environ: prevous environ array
* @env_last_state: last state of chnage
* @index: index of all env var added or modified
* @env_cur_state: cur state of change 0 no change 1 modified 2 added
* @cur_index: cur index of env var modified or added
*/
void free_environ(char **old_environ, int *env_last_state, int *index,
		int env_cur_state, int cur_index)
{
	size_t j = 0;

	if (*env_last_state == 1 && env_cur_state == 1)
	{
		for (j = 0; j < 1024; j++)
		{
			if (cur_index == index[j] && index[j] != -1)
			{
				free(old_environ[cur_index]);
				break;
			}
		}
		index[j] = cur_index;
	}
	else if (*env_last_state == 1 && env_cur_state == 2)
	{
		for (j = 0; j < 1024; j++)
		{
			if (index[j] == -1)
				break;
			free(old_environ[index[j]]);
			index[j] = -1;
		}
	}
	else if (*env_last_state == 2 && env_cur_state == 1)
	{
		free(old_environ[cur_index]);
		index[0] = cur_index;
	}
	else if (*env_last_state == 2 && env_cur_state == 2)
	{
		j = -1;
		while (old_environ[++j])
			if (old_environ[j])
				free(old_environ[j]);
		if (old_environ)
			free(old_environ);
	}
}
