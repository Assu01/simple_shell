#include "main.h"
/**
 * is_in -check if char is in string s
 * @c: char to be checked
 * @s: container string
 * Return: 1 if found else -1
 */
int is_in(char c, char *s)
{
	size_t i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
/**
* words - return number of words in string separated by space
* @s: string buffer
* @sep: word separator
* Return: words count
*/
size_t words(char *s, char *sep)
{
	size_t len, i;

	if (s == NULL)
		return (0);
	len = i = 0;
	while (is_in(s[i], sep))
		i++;
	while (s[i])
	{
		if ((is_in(s[i], sep) && (!is_in(s[i + 1], sep))) || (s[i + 1] == '\0'))
			len++;
		i++;
	}
	if (is_in(s[i - 1], sep))
		len--;

	return (len);
}
/**
* wordcopy -copy word array from string buffer
* @s: string source
* @p: word array pointer
* @sep: word separator
*/
void wordcopy(char *s, char **p, char *sep)
{
	size_t i, j, k;

	i = j = k = 0;
	while (s[i] && is_in(s[i], sep))
		i++;
	while (s[i] && s[i] != '#')
	{
		if (is_in(s[i], sep))
		{
			k = 0;
			j++;
			i++;
			while (is_in(s[i], sep))
				i++;

		}
		else if ((s[i + 1] == '\0' || s[i + 1] == '#') && (!(is_in(s[i], sep))))
		{
			p[j][k] = s[i];
			k = 0;
			j++;
			i++;
		}
		else
		{
			p[j][k] = s[i];
			i++;
			k++;
		}
	}
	p[j] = NULL;
}
/**
* _strtok - split buffer in to words and returns words array
* @s: input buffer
* @p: ouput buffer
* @sep: word separator
* Return: pointer to words array
*/
char *_strtok(char *s, char **p, char *sep)
{
	ssize_t i, j, k;

	if (s == NULL)
		return (NULL);
	i = j = k = 0;
	p = malloc(sizeof(char *) * (words(s, sep) + 1));
	if (p == NULL)
		return (NULL);
	while (s[i] && (is_in(s[i], sep)))
		i++;
	while (s[i] && s[i] != '#')
	{
		if (is_in(s[i], sep) || s[i + 1] == '\0' || s[i + 1] == '#')
		{
			if (s[i + 1] == '\0' || s[i + 1] == '#')
				k++;
			p[j] = malloc(sizeof(char) * (k + 1));
			if (p[j] == NULL)
			{
				for (j = j - 1; j >= 0; j--)
					free(p[j]);
				free(p);
				return (NULL);
			}
			_memset(p[j], k + 1);
			k = 0;
			j++;
			i++;
			while (is_in(s[i], sep))
				i++;
		}
		else
		{
			i++;
			k++;
		}
	}
	wordcopy(s, p, sep);
	return ((char *)p);
}
