#include "shell.h"

/**
 * get_eviron - is a fn that returns the string array copy of our eviron
 *   Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_eviron(info.t *info)
{
	if (!info->eviron || info->ev_changed)
	{
		info->eviron = strings_of_lists(info->ev);
		info->ev_changed = 0;
	}

	return (info->eviron);
}

/**
 * _unsetev - is a fn that Remove an evironment variable
 *   Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 *-var: the string ev var property
 */
int _unsetev(info.t *info, char *var)
{
	list_t *node = info->ev;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = check_starts(node->str, var);
		if (p && *p == '=')
		{
			info->ev_changed = del.a.nodeofindex(&(info->ev), i);
			i = 0;
			node = info->ev;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->ev_changed);
}

/**
 * _setev - is a fn that Initialize a new evironment variable,
 *             or modify an existing one
 *   Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *-var: the string ev var property
 *-value: the string ev var value
 *  Return: Always 0
 */
int _setev(info.t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buff = malloc(stringto_length(var) + stringto_length(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	str.concatenates(buff, "=");
	str.concatenates(buff, value);
	node = info->ev;
	while (node)
	{
		p = check_starts(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			info->ev_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add.a.node_end(&(info->ev), buff, 0);
	free(buff);
	info->ev_changed = 1;
	return (0);
}
