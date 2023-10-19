#include "shell.h"

/**
 *ptr_free - is a fn that frees a pointer and NULLs the address
 *-ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
intptr_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
