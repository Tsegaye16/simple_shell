#include "main.h"
/**
 * copy_info - function that copies information to create
 * a new env or alias
 * @name: name of environment or alias
 * @value: value of environmetn or alias
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}
/**
 * set_env - function that sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int n;
	char *var_env, *name_env;

	for (n = 0; datash->_environ[n]; n++)
	{
		var_env = _strdup(datash->_environ[n]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[n]);
			datash->_environ[n] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, n, sizeof(char *) * (n + 2));
	datash->_environ[n] = copy_info(name, value);
	datash->_environ[n + 1] = NULL;
}
/**
 * _setenv - function that compares environment
 * variables names with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}
/**
 * _unsetenv - function that deletes environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int l, m, n;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	l = -1;
	for (l = 0; datash->_environ[l]; l++)
	{
		var_env = _strdup(datash->_environ[l]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			n = l;
		}
		free(var_env);
	}
	if (n == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (l));
	for (l = m = 0; datash->_environ[l]; l++)
	{
		if (l != n)
		{
			realloc_environ[m] = datash->_environ[l];
			m++;
		}
	}
	realloc_environ[m] = NULL;
	free(datash->_environ[n]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
