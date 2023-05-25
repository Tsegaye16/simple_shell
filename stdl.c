#include "main.h"
/**
 * get_len - function that find the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int get_len(int n)
{
	unsigned int k;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		k = n * -1;
	}
	else
	{
		k = n;
	}
	while (k > 9)
	{
		lenght++;
		k = k / 10;
	}

	return (lenght);
}
/**
 * aux_itoa - function that converts integer to string.
 * @n: integer type number
 * Return: String.
 */
char *aux_itoa(int n)
{
	unsigned int k;
	int lenght = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		k = n * -1;
		buffer[0] = '-';
	}
	else
	{
		k = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (k % 10) + '0';
		k = k / 10;
		lenght--;
	}
	while (k > 0)
		;
	return (buffer);
}

/**
 * _atoi - function that converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int counter = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + counter) != '\0')
	{
		if (size > 0 && (*(s + counter) < '0' || *(s + counter) > '9'))
			break;

		if (*(s + counter) == '-')
			pn *= -1;

		if ((*(s + counter) >= '0') && (*(s + counter) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		counter++;
	}

	for (i = counter - size; i < counter; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
