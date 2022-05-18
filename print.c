
#include "header.h"

/**
 * _print - writes string str to stdout
 * @str: string
 * Return: Nothing
 */
void _print(char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
}
