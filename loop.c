#include "main.h"
/**
 * without_comment - function that deletes comments from input
 *
 * @inp: input string
 * Return: input without comments
 */
char *without_comment(char *inp)
{
	int n, up_to;

	up_to = 0;
	for (n = 0; inp[n]; n++)
	{
		if (inp[n] == '#')
		{
			if (n == 0)
			{
				free(inp);
				return (NULL);
			}

			if (inp[n - 1] == ' ' || inp[n - 1] == '\t' || inp[n - 1] == ';')
				up_to = n;
		}
	}

	if (up_to != 0)
	{
		inp = _realloc(inp, n, up_to + 1);
		inp[up_to] = '\0';
	}

	return (inp);
}
/**
 * shell_loop - function that Loops a shell
 * @datash: data that contains relevant information
 *
 * Return: void.
 */
void shell_loop(data_shell *datash)
{
	int l, i_eof;
	char *input;

	l = 1;
	while (l == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			l = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			l = 0;
			free(input);
		}
	}
}
