#include "shell.h"

/**
 * _return_length - is a fn that returns the length of a string
 * s: the string whose length to check
 *
 * Return: integer length of string
 */
int _return_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _compare_lexo -is a fn that performs lexicogarphic comparison of two strangs.
 * s1: the first strang
 * s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _compare_lexo(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _check_haystack - is a fn that checks if needle starts with haystack
 * haystack: string to search
 * needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *_check_haystack(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * concat_strings - concatenates two strings
 * dest: the destination buffer
 * src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
