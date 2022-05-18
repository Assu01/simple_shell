#include "header.h"

int (*builtins_func[])(char **) = {
	&env_func,
	&exit_func,
	&cd_func,
	&help_func};

/**
 * env_func - prints all environment variables.
 * @args: array of strings
 * Return: 1
 */

int env_func(char **args)
{
	size_t i = 0;

	args = args;
	for (i = 0; environ[i] != NULL; i++)
	{
		_print(environ[i]);
		_print("\n");
	}
	return (1);
}

/**
 * exit_func - exits the shell.
 * @args: array of strings
 * Return: 0
 */

int exit_func(char **args)
{
	args = args;
	return (0);
}

/**
 * cd_func - changes directory
 * @args: array of strings
 * Return: out
 */
int cd_func(char **args)
{
	if (!args[1])
		chdir(getenv("HOME"));
	else if (args[1][0] == '-')
	{
		chdir(getenv("OLDPWD"));
		_print(getenv("OLDPWD"));
		_putchar('\n');
	}
	else if (chdir(args[1]) != 0)
		perror("no dir");
	return (1);
}

/**
 * help_func - prints command help message
 * @args: array of strings
 * Return: out
 */
int help_func(char **args)
{
	if (!args[1])
	{
		_print("Simple Shell Help!\n");
		_print("Type program names and hit enter.\n");
		_print("The following are built in: exit, cd, env\n");
		return (1);
	}

	if (_strcmp(args[1], "exit") == 0)
	{
		_print("exit: exit");
		_print("\tExit the shell.\n");
		_print("\n");
		_print("\tExits the shell with a status of N.\n");
		_print("\tIf N is omitted, the exit status is");
		_print("that of the last command executed.\n");
	}

	if (_strcmp(args[1], "cd") == 0)
	{
		_print("cd: cd [-L|[-P [-e]] [-@]] [dir]\n");
		_print("\tChange the shell working directory.\n");
		_print("\n");
		_print("\tChange the current directory to DIR.");
		_print("The default DIR is the value of the HOME shell variable.\n");
	}

	if (_strcmp(args[1], "env") == 0)
	{
		_print("env\n");
		_print("\tPrints all environment variables.\n");
		_print("\n");
	}
	return (1);
}
