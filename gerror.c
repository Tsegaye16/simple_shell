#include "main.h"
/**
 * get_error - function that calls the error accordingly
 * @datash: data that contains relevent informations
 * @e_val: error value
 * Return: error
 */
int get_error(data_shell *datash, int e_val)
{
	char *error;

	switch (e_val)
	{
	case -1:
		error = error_env(datash);
		break;
	case 126:
		error = error_path_126(datash);
		break;
	case 127:
		error = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = e_val;
	return (e_val);
}
