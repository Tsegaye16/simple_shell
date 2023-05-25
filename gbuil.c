#include "main.h"

/**
 * get_builtin - function that pias the command in arguments
 * @cmd: command nam
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int n;

	for (n = 0; builtin[n].name; n++)
	{
		if (_strcmp(builtin[n].name, cmd) == 0)
			break;
	}

	return (builtin[n].f);
}
