#include "main.h"
/**
 * free_data - function that make frees data structure
 *
 * @datash: data contains relevant information
 * Return: return void
 */
void free_data(data_shell *datash)
{
	unsigned int k;

	for (k = 0; datash->_environ[k]; k++)
	{
		free(datash->_environ[k]);
	}

	free(datash->_environ);
	free(datash->pid);
}
/**
 * set_data - function that initialize data structure
 *
 * @datash: relevant data
 * @av: argument vector
 * Return: return void
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int k;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (k = 0; environ[k]; k++)
		;

	datash->_environ = malloc(sizeof(char *) * (k + 1));

	for (k = 0; environ[k]; k++)
	{
		datash->_environ[k] = _strdup(environ[k]);
	}

	datash->_environ[k] = NULL;
	datash->pid = aux_itoa(getpid());
}
/**
 * main - Entry point
 *
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
