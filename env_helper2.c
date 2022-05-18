#include "main.h"
/**
* _unsetenv - unset environmenta var
* @name: env var to delete
* Return: 2 if success else -1
*/
int _unsetenv(const char *name)
{
	size_t j = 0;
	int index;
	char *var;

	var = _getenv(name);
	if (var == NULL)
		return (-1);
	index = _getindex(name);
	while (environ[index][j])
	{
		environ[index][j] = '\0';
		j++;
	}
	free(var);
	return (2);
}

/**
* free_null_env - free memory if fail during allocation
* @newenv: new environmental var pointer
* @i: failed index
* Return: -1 always
*/
int free_null_env(char **newenv, ssize_t i)
{
	i--;
	while (i >= 0)
	{
		free(newenv[i]);
		i--;
	}
	free(newenv);
	return (0);
}
/**
* free_env - free environment variable after setenv call
* @en: environ var
* @status: return value of setenv call
* @index: new index of env var set by setenv call
*/
void free_env(char **en, int status, int index)
{
	size_t set = 0;

	if (status == 0)
		free(en[index]);
	else if (status == 1)
	{
		while (en[set])
		{
			free(en[set]);
			set++;
		}
		free(en);
	}
}
