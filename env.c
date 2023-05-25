#include "main.h"
/**
 * cmp_env_name - function that compares environment variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int n;

	for (n = 0; nenv[n] != '='; n++)
	{
		if (nenv[n] != name[n])
		{
			return (0);
		}
	}

	return (n + 1);
}
/**
 * _getenv - function that get an environment variable
 * @name: environment variable name
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int n, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (n = 0; _environ[n]; n++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[n], name);
		if (mov)
		{
			ptr_env = _environ[n];
			break;
		}
	}

	return (ptr_env + mov);
}
/**
 * _env - function that displays evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int m, n;

	for (m = 0; datash->_environ[m]; m++)
	{

		for (n = 0; datash->_environ[m][n]; n++)
			;

		write(STDOUT_FILENO, datash->_environ[m], n);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
