#include "main.h"
/**
 * check_env - function that checks wearher the
 * typed variable is an env variable
 *
 * @h: list's head
 * @inp: input string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var **h, char *inp, data_shell *data)
{
	int row, chr, k, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (k = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, k, _envr[row] + chr + 1, lval);
				return;
			}

			if (inp[k] == _envr[row][chr])
				k++;
			else
				break;
		}
	}

	for (k = 0; inp[k]; k++)
	{
		if (inp[k] == ' ' || inp[k] == '\t' || inp[k] == ';' || inp[k] == '\n')
			break;
	}

	add_rvar_node(h, k, NULL, 0);
}
/**
 * check_vars - function that check weather the typed variable is $$ or $?
 *
 * @h: list's head
 * @inp: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *inp, char *st, data_shell *data)
{
	int k, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (k = 0; inp[k]; k++)
	{
		if (inp[k] == '$')
		{
			if (inp[k + 1] == '?')
				add_rvar_node(h, 2, st, lst), k++;
			else if (inp[k + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), k++;
			else if (inp[k + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (inp[k + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (inp[k + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (inp[k + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (inp[k + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, inp + k, data);
		}
	}

	return (k);
}
/**
 * replaced_input - function that replaces string into variables
 *
 * @head: list's head
 * @input: input string
 * @new_input: new replaced string
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int l, m, n;

	indx = *head;
	for (m = l = 0; l < nlen; l++)
	{
		if (input[m] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[l] = input[m];
				m++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (n = 0; n < indx->len_var; n++)
					m++;
				l--;
			}
			else
			{
				for (n = 0; n < indx->len_val; n++)
				{
					new_input[l] = indx->val[n];
					l++;
				}
				m += (indx->len_var);
				l--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[l] = input[m];
			m++;
		}
	}

	return (new_input);
}
/**
 * rep_var - functions that calls functions to replace string into vars
 *
 * @inp: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *inp, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, inp, status, datash);

	if (head == NULL)
	{
		free(status);
		return (inp);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, inp, new_input, nlen);

	free(inp);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
