#include "header.h"

/**
* _strcmp - compares two strings
* @s1: first string
* @s2: second string
* Return: int value
*/

int _strcmp(char *s1, char *s2)
{
	while ((*s1 && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}

/**
* _strncmp - compares two strings
* @s1: first string
* @s2: second string
* @n: number of bytes to compare
* Return: int value
*/

int _strncmp(char *s1, char *s2, size_t n)
{

	if (n == 0)
		return (0);
	do {
		if (*s1 != *s2++)
			return (*s1 - *s2 - 1);
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
}
