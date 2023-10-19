#include "shell.h"

/**
 **_strncpy - is a fn that  copies a string
 *-dstination: the dstinationination string to be copied to
 *-source: the source string
 *-n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dstination, char *source, int n)
{
	int i, j;
	char *s = dstination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		dstination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dstination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat -is a fn that  concatenates two strings
 *-dstination: the first string
 *-source: the second string
 *-n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dstination, char *source, int n)
{
	int i, j;
	char *s = dstination;

	i = 0;
	j = 0;
	while (dstination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		dstination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		dstination[i] = '\0';
	return (s);
}

/**
 **locate-char - is a fn that locates a character in a string
 *-s: the string to be parsed
 *-c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *locate-char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}


==================================================================
                      stri.functions4.c                         


#include "shell.h"

/**
 * **splittow - is a fn that  splits a string into words. Repeat delimiters are ignored
 *-str: the input string
 *-d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **splittow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!ch_delim(str[i], d) && (ch_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (ch_delim(str[i], d))
			i++;
		k = 0;
		while (!ch_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **splittow2 -is a fn that splits a string into words
 *-str: the input string
 *-d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splittow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
