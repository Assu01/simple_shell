#include "shell.h"

/**
 * _strlen - returns the length of a null-terminated string
 * @str: string
 *
 * Return: length of string, minus null terminator
 */

int _strlen(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return (len);
}


/**
 * _strcat - concatenates two strings
 * @dest: destination char
 * @src: source char
 * Return: new char
 */

char *_strcat(char *dest, char *src)
{
	int i;
	int n = 0;

	while (dest[n] != '\0')
	{
		n++;
	}
	for (i = 0 ; i < n && src[i] != '\0' ; i++)
		dest[n + i] = src[i];
	dest[n + i] = '\0';

	return (dest);
}


/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * @str: string
 * Return: pointer to newly allocated space in memory
 */

char *_strdup(char *str)
{
	int length, i;
	char *arr;

	length = 0;
	if (str == NULL)
		return (NULL);

	length = _strlen(str);

	arr = malloc((length + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);

	for (i = 0; i < length; i++)
		arr[i] = str[i];

	arr[i] = '\0';

	return (arr);
}
