#include "shell.h"

/**
 * _strcpy -is a fn that  copies a string
 *-dstination: the dstinationination
 *-source: the source
 *
 * Return: pointer to dstinationination
 */
char *_strcpy(char *dstination, char *source)
{
	int i = 0;

	if (dstination == source || source == 0)
		return (dstination);
	while (source[i])
	{
		dstination[i] = source[i];
		i++;
	}
	dstination[i] = 0;
	return (dstination);
}

/**
 * _strdup - is a fn that duplicates a string
 *-str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int lengths = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lengths++;
	ret = malloc(sizeof(char) * (lengths + 1));
	if (!ret)
		return (NULL);
	for (lengths++; lengths--;)
		ret[lengths] = *--str;
	return (ret);
}

/**
 *_puts - is a fn that prints an input string
 *-str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar -is a fn that  writes the character c to stdout
 *-c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buff[WRITE_buff_SIZE];

	if (c == buff_FLUSH || i >= WRITE_buff_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != buff_FLUSH)
		buff[i++] = c;
	return (1);
}
