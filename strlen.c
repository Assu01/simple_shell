
/**
* _strlen - compares two strings
* @str: first string
* Return: length of string
*/

int _strlen(char *str)
{
	unsigned int len = 0;

	while (str[len])
		len++;
	return (len);
}
