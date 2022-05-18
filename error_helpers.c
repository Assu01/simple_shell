#include "shell.h"

/**
 * command_error - prints error message when command is not found
 * @NAME: name of program
 * @command: command not found
 *
 */

void command_error(__attribute__((unused)) char *NAME, char *command)
{
	write(STDOUT_FILENO, command, _strlen(command));
	write(STDOUT_FILENO, ": command not found\n", 20);
}

/**
 * exec_error - prints error message when command fails to execute
 * @NAME: name of program
 * @command: name of command
 */

void exec_error(char *NAME, char *command)
{
	write(STDOUT_FILENO, NAME, _strlen(NAME));
	write(STDOUT_FILENO, ": ", 2);
	perror(command);
}
