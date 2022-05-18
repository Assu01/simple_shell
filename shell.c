 #include "shell.h"

int _strlen(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len + 1);
}


int count_args(char *user_input)
{
	int args, i;

	args = 1;
	i = 0;
	while (user_input[i] != '\0' && user_input[i] != '\n')
	{
		if (user_input[i] == ' ')
			args++;
		i++;
	}
	return (args);
}


void get_command(char *user_input, int args)
{
	int compare, status, i, length;
	pid_t child_pid;
	char *token;
	char **argv;

	compare = strncmp("exit", user_input, 4);
	if (compare == 0)
	{
		free(user_input);
		exit (0);
	}

	length = 0;
	argv = malloc(sizeof(char *) * (args + 1));

	status = 1;

	token = strtok(user_input, " \n");
	length = _strlen(token);
	argv[0] = malloc(sizeof(char) * length);
	argv[0] = token;
	token = strtok(NULL, " \n");
	for (i = 1; token != NULL; i++)
	{
		length = _strlen(token);
		argv[i] = malloc(sizeof(char) * length);
		argv[i] = token;
		token = strtok(NULL, " \n");
	}

	argv[i] = '\0';

	child_pid = fork();
		if (child_pid == 0)
		{
			if (execvp(argv[0], argv) != 0)
				perror("./hsh");

			for (i = 0; i < args; i++)
				free(argv[i]);
			free(argv);
		}
		else
			wait(&status);

}

/**
 * main - simple shell
 * Return: 0 (Always)
 */

int main(void)
{
	int bytes_read, args;
	char *user_input;
	size_t nbytes;

	nbytes = 1024;
	while (nbytes != 0)
	{
		write(STDOUT_FILENO, "$ ", 2);
		user_input = malloc(sizeof(char) * nbytes);
		if (user_input == NULL)
		{
			perror("malloc\n");
			break;
		}
		bytes_read = getline(&user_input, &nbytes, stdin);
		if (bytes_read == -1)
		{
			perror("getline\n");
			break;
		}
		args = count_args(user_input);
		get_command(user_input, args);
	}
	free(user_input);
	return (0);
}
