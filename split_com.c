#include "main.h"
/**
 * swap_char - function that swaps | and & for non-printed characters
 *
 * @inp: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_char(char *inp, int bool)
{
	int k;

	if (bool == 0)
	{
		for (k = 0; inp[k]; k++)
		{
			if (inp[k] == '|')
			{
				if (inp[k + 1] != '|')
					inp[k] = 16;
				else
					k++;
			}

			if (inp[k] == '&')
			{
				if (inp[k + 1] != '&')
					inp[k] = 12;
				else
					k++;
			}
		}
	}
	else
	{
		for (k = 0; inp[k]; k++)
		{
			inp[k] = (inp[k] == 16 ? '|' : inp[k]);
			inp[k] = (inp[k] == 12 ? '&' : inp[k]);
		}
	}
	return (inp);
}
/**
 * add_nodes - function that add separators and command lines in the lists
 *
 * @head_s: separator list's head
 * @head_l: head of command lines list
 * @inp: input string
 * Return: no return
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *inp)
{
	int k;
	char *line;

	inp = swap_char(inp, 0);

	for (k = 0; inp[k]; k++)
	{
		if (inp[k] == ';')
			add_sep_node_end(head_s, inp[k]);

		if (inp[k] == '|' || inp[k] == '&')
		{
			add_sep_node_end(head_s, inp[k]);
			k++;
		}
	}

	line = _strtok(inp, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}
/**
 * go_next - function that go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data that contains relevant information
 * Return: no return
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}
/**
 * split_commands - function that splits command lines accordingly
 *
 * @datash:relevant data
 * @input: inp string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - function that tokenizes the input string
 *
 * @inp: input string.
 * Return: string splitted.
 */
char **split_line(char *inp)
{
	size_t bsize;
	size_t k;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(inp, TOK_DELIM);
	tokens[0] = token;

	for (k = 1; token != NULL; k++)
	{
		if (k == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, k, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[k] = token;
	}

	return (tokens);
}
