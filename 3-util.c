#include "main.h"
/**
* getenv_index - get env var value given its name
* @name: env var name
* Return: value of var
*/
char *getenv_index(char *name)
{
	int index = _getindex(name);
	char *p;
	int i = 0;

	if (index == -1)
		return (NULL);
	p = environ[index];
	while (p[i] != '=')
		i++;
	return (&p[++i]);
}
/**
* _strcmp_index - compare strings until only end of src string
* @src: source string
* @dest: destination string
* Description: if upto all chars of src are equal to start of dest
*               returns 0 else -1
* Return: 0 on success  -1 on failure
*/
int _strcmp_index(char *src, char *dest)
{
	size_t i = 0;

	while (src[i] && dest[i])
	{
		if (src[i] != dest[i])
			break;
		i++;
	}
	if (src[i] == '\0')
		return (0);
	return (-1);
}
