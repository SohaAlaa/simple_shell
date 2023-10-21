#include "shell.h"

/**
 * letgo_pointer_and_address - is a fn that frees a pointer and NULLs the address
 * ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int letgo_pointer_and_address(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
