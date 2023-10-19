#include "shell.h"

/**
 **_memoryset - is a fn that fills memory with a constant byte
 *-s: the pointer to the memory area
 *-b: the byte to fill *s with
 *-n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memoryset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * full.free - is a fn that frees a string of strings
 *-pp: string of strings
 */
void full.free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - is a fn that reallocates a block of memory
 *-ptr: pointer to previous malloc'ated block
 *-theoldsize: byte size of previous block
 *-thenewsize: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int theoldsize, unsigned int thenewsize)
{
	char *p;
if (!ptr)
		return (malloc(thenewsize));
	if (!thenewsize)
		return (free(ptr), NULL);
	if (thenewsize == theoldsize)
		return (ptr);

	p = malloc(thenewsize);
	if (!p)
		return (NULL);

	theoldsize = theoldsize < thenewsize ? theoldsize : thenewsize;
	while (theoldsize--)
		p[theoldsize] = ((char *)ptr)[theoldsize];
	free(ptr);
	return (p);
}
