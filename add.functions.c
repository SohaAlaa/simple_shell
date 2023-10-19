#include "shell.h"

/**
 * _interact -is a fn thats returns true if shell is _interact mode
 *   struct address
 *
 * Return: 1 if _interact mode, 0 otherwise
 */
int _interact(info.t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * ch_delim - is a fn that checks if character is a delimeter
 *-c: the char to check
 *-delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int ch_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *ch_alpha -is a fn that checks for alphabetic character
 *-c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int ch_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *fn.atoi - is a fn that converts a string to an integer
 *-s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int fn.atoi(char *s)
{
	int i, sign = 1, _flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && _flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			_flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (_flag == 1)
			_flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
