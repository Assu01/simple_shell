#include "main.h"

/**
 * _putchar - print character
 * @p: char to be print
 *
 * Description: print char
 *
 * Return: 1
 */

int _putchar(char p)
{
	char s = p;

	write(1, &s, 1);

	return (1);
}
