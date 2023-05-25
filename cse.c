#include "main.h"
/**
 * repeated_char - function that counts the repetitions of a character
 *
 * @input: input string
 * @in: index
 * Return: repetitions
 */
int repeated_char(char *input, int in)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, in + 1));

	return (in);
}

/**
 * error_sep_op - function that gets syntax errors
 *
 * @input: input string
 * @in: index
 * @last: last character read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *input, int in, char last)
{
	int counter;

	counter = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, in + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (in);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (in);

		if (last == '|')
		{
			counter = repeated_char(input, 0);
			if (counter == 0 || counter > 1)
				return (in);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (in);

		if (last == '&')
		{
			counter = repeated_char(input, 0);
			if (counter == 0 || counter > 1)
				return (in);
		}
	}

	return (error_sep_op(input + 1, in + 1, *input));
}
/**
 * first_char - function that finds index of the first character
 *
 * @input: input string
 * @in: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *in)
{

	for (*in = 0; input[*in]; *in += 1)
	{
		if (input[*in] == ' ' || input[*in] == '\t')
			continue;

		if (input[*in] == ';' || input[*in] == '|' || input[*in] == '&')
			return (-1);

		break;
	}

	return (0);
}
/**
 * print_syntax_error - function that displays when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @in: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error(data_shell *datash, char *input, int in, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[in] == ';')
	{
		if (bool == 0)
			msg = (input[in + 1] == ';' ? ";;" : ";");
		else
			msg = (input[in - 1] == ';' ? ";;" : ";");
	}

	if (input[in] == '|')
		msg = (input[in + 1] == '|' ? "||" : "|");

	if (input[in] == '&')
		msg = (input[in + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}
/**
 * check_syntax_error - intermediate function to display
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int n = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	n = error_sep_op(input + begin, 0, *(input + begin));
	if (n != 0)
	{
		print_syntax_error(datash, input, begin + n, 1);
		return (1);
	}

	return (0);
}
