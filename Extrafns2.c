#include "shell.h"

/**
 * _conv_str_int - is a fn that converts a string to an integer
 * s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _conv_str_int(char *s)
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
 * msg_wrong - is a fn that prints an error message
 * info: the parameter & return info struct
 * estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void msg_wrong(info_t *info, char *estr)
{
	_prt_ip_str(info->fname);
	_prt_ip_str(": ");
	prt_decimal(info->line_count, STDERR_FILENO);
	_prt_ip_str(": ");
	_prt_ip_str(info->argv[0]);
	_prt_ip_str(": ");
	_prt_ip_str(estr);
}

/**
 * prt_decimal - is a fn that function prints a decimal (integer) number (base 10)
 * input: the input
 * fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int prt_decimal(int input, int fd)
{
	int (*_wr_charC_out)(char) = wr_charC_out;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_wr_charC_out = _wr_char_c;
	if (input < 0)
	{
		_abs_ = -input;
		_wr_charC_out('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_wr_charC_out('0' + current / i);
			count++;
		}
		current %= i;
	}
	_wr_charC_out('0' + current);
	count++;

	return (count);
}

/**
 * cloneCvrt - is a fn that converter function, a clone of itoa
 * num: number
 * base: base
 * flags: argument flags
 *
 * Return: string
 */
char *cloneCvrt(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
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
 * no_cmm - is a fn that function replaces first instance of '#' with '\0'
 * buf: address of the string to modify
 *
 * Return: Always 0;
 */
void no_cmm(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
