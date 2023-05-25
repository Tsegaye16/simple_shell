#include "main.h"
/**
 * _strcat - function that concatenate two strings
 * @desti: destination string
 * @sorc: source string
 * Return: the dest
 */
char *_strcat(char *desti, const char *sorc)
{
	int m;
	int n;

	for (m = 0; desti[m] != '\0'; m++)
		;

	for (n = 0; sorc[n] != '\0'; n++)
	{
		desti[m] = sorc[n];
		m++;
	}

	desti[m] = '\0';
	return (desti);
}
/**
 * _strcpy - function that copies the string pointed to by src.
 * @desti: Type char pointer the destination of the copied string
 * @sorc: Type char pointer the source of string
 * Return: the destination.
 */
char *_strcpy(char *desti, char *sorc)
{

	size_t k;

	for (k = 0; sorc[k] != '\0'; k++)
	{
		desti[k] = sorc[k];
	}
	desti[k] = '\0';

	return (desti);
}
/**
 * _strcmp - comparing two strings.
 * @s1: strring1 to be compared
 * @s2: string2 to be compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int k;

	for (k = 0; s1[k] == s2[k] && s1[k]; k++)
		;

	if (s1[k] > s2[k])
		return (1);
	if (s1[k] < s2[k])
		return (-1);
	return (0);
}
/**
 * _strchr - function that locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int n = 0;

	for (; *(s + n) != '\0'; n++)
		if (*(s + n) == c)
			return (s + n);
	if (*(s + n) == c)
		return (s + n);
	return ('\0');
}
/**
 * _strspn - function that finds the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int a, b, bool;

	for (a = 0; *(s + a) != '\0'; a++)
	{
		bool = 1;
		for (b = 0; *(accept + b) != '\0'; b++)
		{
			if (*(s + a) == *(accept + b))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (a);
}
