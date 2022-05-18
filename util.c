#include <stdio.h>
/**
 * _strlen - return length of string
 * @s: string to be checked
 *
 * Description: return length of string with null terminator char
 *
 * Return: length
 */
size_t _strlen(const char *s)
{
	size_t i = 0;

	if (s == NULL)
		return (0);

	while (s[i])
		i++;
	i++;

	return (i);
}
/**
 * _strcmp -compare two string
 * @src: first string
 * @dest: second string
 *
 * Description: compare and return 0 if equal else -1
 *
 * Return: 0 if equal else -1
 */
int _strcmp(char *src, char *dest)
{
	size_t i = 0;

	if (src == NULL || dest == NULL)
		return (-1);
	while (src[i] && dest[i])

	{
		if (src[i] != dest[i])
			return (-1);
		i++;
	}
	if (src[i] != '\0' || dest[i] != '\0')
		return (-1);
	return (0);
}
/**
 * _strcpy - copy src string to dest string
 * @src: source string
 * @dest: dest string
 *
 * Description: make sure size of src < size of dest ,
 *		else buffer over run occur
 *		also it does not copy null terminator
 * Return: 0 if success -1 if failed
 */
int _strcpy(char *src, char *dest)
{
	size_t i = 0;

	if (src == NULL || dest == NULL)
		return (-1);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (0);
}
/**
 * _memset - reset memory to null bytes
 * @mem: memory pointer
 * @size: size of memory to be cleared
 *
 * Return: 0 if success  -1 on fail
 */
int _memset(char *mem, size_t size)
{
	size_t i;

	if (mem == NULL)
		return (-1);
	for (i = 0; i < size; i++)
		mem[i] = '\0';

	return (0);
}
/**
 * len_from_to - count chars from some index upto char stop
 * @p: string
 * @start: start of count index
 * @stop: stoping char
 *
 * Return: number of chars from star to stop but not including
 */
size_t len_from_to(char *p, int start, char stop)
{
	size_t i, len = 0;

	if (p == NULL)
		return (0);
	i = start;
	while (p[i] != stop && p[i])
	{
		len++;
		i++;
	}

	return (len);
}
