#include "shell.h"

/**
 * _true_shell_intact_mode - is a fn that returns true if shell is _true_shell_intact_mode mode
 * info: struct address
 *
 * Return: 1 if _true_shell_intact_mode mode, 0 otherwise
 */
int _true_shell_intact_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 *_char_is_deli - is a fn that checks if character is a delimeter
 * c: the char to check
 * delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int_char_is_deli(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * fn_checks_alphabchar - is a fn that checks for alphabetic character
 *c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int  fn_checks_alphabchar(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *conv_a_str_to_int - is a fn that converts a string to an integer
 *s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int conv_a_str_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
