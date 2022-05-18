#include "main.h"
/**
 * _getenv - get enviroment variable
 * @name: name
 *
 * Return: Full name
 */
char *_getenv(const char *name)
{
	size_t i = 0, j = 0;

	while (environ[i])
	{
		while (name[j])
		{
			if (name[j] != environ[i][j])
				break;
			j++;
		}
		if (name[j] == '\0' && environ[i][j] == '=')
			return (&environ[i][j + 1]);
		i++;
		j = 0;
	}
	return (NULL);
}
/**
 * _getindex - get index
 * @name: Name
 *
 * Return: index
 */
int  _getindex(const char *name)
{
	int i = 0, j = 0;

	if (name == NULL)
		return (-1);
	while (environ[i])
	{
		while (name[j])
		{
			if (name[j] != environ[i][j])
			{
				break;
			}
			j++;
		}
		if (name[j] == '\0' && environ[i][j] == '=')
			return (i);
		i++;
		j = 0;
	}
	return (-1);
}
/**
 * set_state - set state of last change in env var array
 * @env_last_state: pointer to env_last_state var
 * @cur_index: pointer to cur_index var
 * @cur_state: pointer to cur_state var
 * @add_case: if new var add or only modified
 * @sizeenv: new env array size
 * Return: always 2
 */
int set_state(int *env_last_state, int *cur_index,
	int *cur_state, int *add_case, int sizeenv)
{
	*env_last_state = 2;
	*cur_index = sizeenv - 2;
	*cur_state = 2;
	*add_case = 1;
	return (2);
}
/**
* _addenv - add new environmental var
* @name: new name to be added
* @value: new value added
* @env_last_state: last change state
* @index: index of all changed vars
* @cur_state: cur state of change
* @cur_index: cur changed index
* @add_case: if any add or modifed
* Return: 1 if added 0 if No change or failed to add
*/
int  _addenv(const char *name, const char *value, int *env_last_state,
	int *index, int *cur_state, int *cur_index, int *add_case)
{
	size_t sizeenv, size, i = 0, j = 0, k = 0;
	char **newenv;

	while (environ[i])
		i++;
	sizeenv = i + 2;
	newenv = malloc(sizeof(char *) * (i  + 2));
	if (newenv == NULL)
		return (0);
	for (i = 0; i < sizeenv - 1; i++)
	{
		if (environ[i])
			size = _strlen(environ[i]);
		else
			size = _strlen(name) + _strlen(value)  - 1;
		newenv[i] = malloc(sizeof(char) * (size));
		if (newenv[i] == NULL)
			return (free_null_env(newenv, i));
		_memset(newenv[i], size);
		if (environ[i])
			for (k = 0; k <= size - 1; k++)
				newenv[i][k] = environ[i][k];
		else
		{
			for (k = 0; k < _strlen(name) - 1; k++)
				newenv[i][k] = name[k];
			j = _strlen(name) - 1;
			newenv[i][j] = '=';
			j++;
			for (k = 0; k < _strlen(value) - 1; k++)
				newenv[i][k + j] = value[k];
		}
		j = 0;
	}
	newenv[sizeenv - 1] = NULL;
	free_environ(environ, env_last_state, index, 2,  sizeenv - 2);
	environ = newenv;
	return (set_state(env_last_state, cur_index, cur_state, add_case, sizeenv));
}
/**
* _setenv -set or add new environmental var
* @name: name of new env var
* @value: value to be asigned to new var
* @ow: what to do if value already exist /pass or overwrite
* @env_last_state: last state of change
* @Last_index: index of all chaged var
* @cur_state: cur state of change
* @cur_index: cur modifed var index
* @add_case: if any var added
* Return: 0 no change or if failed 1 if modfied 2 if added new var
*/
int _setenv(const char *name, const char *value, int ow, int *env_last_state,
	int *Last_index, int *cur_state, int *cur_index, int *add_case)
{
	size_t lenName, lenValue;
	int index, i = -1, j = -1;
	char *tmp;

	if (name == NULL)
		return (0);
	if (_getenv(name) == NULL)
		return (_addenv(name, value, env_last_state,
			Last_index, cur_state, cur_index, add_case));
	if (ow == 0)
		return (0);
	if (_getenv(name))
	{
		index = _getindex(name);
		lenName = _strlen(name);
		lenValue = _strlen(value);
		tmp = malloc(sizeof(char) * (lenName + lenValue + 1));
		if (tmp == NULL)
			return (0);
		free_environ(environ, env_last_state, Last_index, 1, index);
		environ[index] = tmp;
		while (name[++i])
			environ[index][i] = name[i];
		environ[index][i] = '=';
		i++;
		while (value[++j])
			environ[index][i + j] = value[j];
		*env_last_state = 1;
		*cur_state = 1;
		j = 0;
		*cur_index = _getindex(name);

		while (Last_index[j] != -1 && (*cur_index != Last_index[j]))
			j++;
		if (Last_index[j] == -1)
			Last_index[j] = *cur_index;
		return (1);
	}
	return (0);
}
