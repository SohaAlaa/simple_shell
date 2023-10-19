#include "shell.h"

/**
 * stringto_intger - is a fn that converts a string to an integer
 *-s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int stringto_intger(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printsthe.er - is a fn that prints an error message
 *   the parameter & return info struct
 *-estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printsthe.er(info.t *info, char *estr)
{
	eputs(info->fname);
	eputs(": ");
	prt-decimal(info->line_count, STDERR_FILENO);
	eputs(": ");
	eputs(info->argv[0]);
	eputs(": ");
	eputs(estr);
}

/**
 * prt-decimal - is a fn that function prints a decimal (integer) number (base 10)
 *-input: the input
 *-fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int prt-decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eput.ch;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * cvrt_no - is a fn that converter function, a clone of itoa
 *-num: number
 *-base: base
 *-_flags: argument _flags
 *
 * Return: string
 */
char *cvrt_no(long int num, int base, int _flags)
{
	static char *array;
	static char bufffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(_flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = _flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &bufffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rmvcomment - is a fn that function replaces first instance of '#' with '\0'
 *-buff: address of the string to modify
 *
 * Return: Always 0;
 */
void rmvcomment(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
