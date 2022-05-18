#include "header.h"

/**
 * split_str - splits a string into tokens
 * @buf: The character to print
 * Return: array of strings.
 */
char **split_str(char *buf)
{
	char *token, **eachstr, *delim;
	int count = 0;

	delim = " \t\r\n\a";
	eachstr = malloc(sizeof(*eachstr) * 100);
	if (!eachstr)
		return (NULL);

	token = strtok(buf, delim);
	while (token)
	{
		eachstr[count] = token;
		token = strtok(NULL, delim);
		count++;
	}
	eachstr[count] = NULL;

	return (eachstr);
}

/**
 * main - the main program for shell.
 * @ac: Arguments numbers.
 * @av: string arguments.
 * Return: 0 always.
 */
int main(int ac, char **av)
{
	unsigned int status = 1;
	char *userinput = NULL, **args;
	size_t userinput_size = 1;
	int line, counter = 1;

	signal(SIGINT, SIG_IGN);
	ac = ac;

	while (status)
	{
		userinput = malloc(userinput_size);
		if (!userinput)
		{
			_print("Failed, can not allocate memory!");
			exit(EXIT_FAILURE);
		}
		if (isatty(STDIN_FILENO))
			_print("($) ");
		line = getline(&userinput, &userinput_size, stdin);
		if (line == -1)
		{
			status = 0;
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			free(userinput);
			exit(EXIT_SUCCESS);
		}
		args = split_str(userinput);
		status = execute(av[0], args, counter);

		counter++;
		free(userinput);
		free(args)
;	}

	return (0);
}
