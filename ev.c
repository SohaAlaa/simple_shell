#include "shell.h"

/**
 * _myev - is a fn that prints the current evironment
 *   Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myev(info.t *info)
{
	printliststring(info->ev);
	return (0);
}

/**
 * _getev - is a fn that gets the value of an eviron variable
 *   Structure containing potential arguments. Used to maintain
 *-name: ev var name
 *
 * Return: the value
 */
char *_getev(info.t *info, const char *name)
{
	list_t *node = info->ev;
	char *p;

	while (node)
	{
		p = check_starts(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 *_mysetev -  is a fn that Initialize a new evironment variable,
 *             or modify an existing one
 *   Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int_mysetev(info.t *info)
{
	if (info->argc != 3)
	{
		eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setev(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetev - is a fn that Remove an evironment variable
 *   Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetev(info.t *info)
{
	int i;

	if (info->argc == 1)
	{
		eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetev(info, info->argv[i]);

	return (0);
}

/**
 * populate_ev_list - is a fn that populates ev linked list
 *   Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_ev_list(info.t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; eviron[i]; i++)
		add.a.node_end(&node, eviron[i], 0);
	info->ev = node;
	return (0);
}
