#include "header.h"

/**
 *printnum - prints number
 *@n: number
 */

void printnum(int n)
{
	if (n < 0)
	{
		_putchar('-');
		n = -n;
	}

	if (n == 0)
		_putchar('0');

	if (n / 10 != 0)
		printnum(n / 10);

	_putchar(n % 10 + '0');
}

/**
 *errormsg - run a command
 *@args: the command extracted from shell.c
 *@filename: name of main program
 *@count: counts number of executions
 */
void errormsg(char *filename, char *args, int count)
{
	_print(filename);
	_print(": ");
	printnum(count);
	_print(": ");
	_print(args);
	_print(": not found\n");
}

/**
 *execute - run a command
 *@args: the command extracted from shell.c
 *@filename: name of main program
 *@count: counts number of executions
 *Return: 1 or 0 depending on command executed
 */

int execute(char *filename, char **args, int count)
{
	int i, id, status;
	/*
	*char *firstarg = args[0];
	*/
	char *builtins_cmd[] = {"env", "exit", "cd", "help"};
	int builtins_num = sizeof(builtins_cmd) / sizeof(char *);

	if (!args[0])
		return (1);
	for (i = 0; i < builtins_num; i++)
	{
		if (_strcmp(args[0], builtins_cmd[i]) == 0)
			return ((*builtins_func[i])(args));
	}
	/*
	*	if (_strncmp(firstarg, "/", 1) != 0)
	*	firstarg = _strcat(args[0]);
	*/
	if (access(args[0], X_OK))
	{
		errormsg(filename, args[0], count);
		return (1);
	}
	id = fork();
	if (id < 0)
	{
		_print("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("error");
		}
		exit(EXIT_FAILURE);
	}
	else
		wait(&status);
	return (1);
}
