#include "shell.h"

/**
 * stringto_length - is a fn that returns the lengths of a string
 *-s: the string whose lengths to check
 *
 * Return: integer lengths of string
 */
int stringto_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * strings_comparison -is a fn that  performs lexicogarphic comparison of two strangs.
 *-s1: the first strang
 *-s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int strings_comparison(char *s1, char *s2)
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
 * check_starts -is a fn that  checks if needle starts with haystack
 *-haystack: string to search
 *-needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *check_starts(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * str.concatenates -is a fn that concatenates two strings
 *-dstination: the dstinationination bufffer
 *-source: the source bufffer
 *
 * Return: pointer to dstinationination bufffer
 */
char *str.concatenates(char *dstination, char *source)
{
	char *ret = dstination;

	while (*dstination)
		dstination++;
	while (*source)
		*dstination++ = *source++;
	*dstination = *source;
	return (ret);
}
