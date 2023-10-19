#include "shell.h"

/**
 * _mhistory - is a fn displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 *   Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mhistory(info.t *info)
{
	print.the.list(info->history);
	return (0);
}

/**
 * un.set.alias - is a fn that sets alias to string
 *   parameter struct
 *-str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int un.set.alias(info.t *info, char *str)
{
	char *p, c;
	int ret;

	p = locate-char(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del.a.nodeofindex(&(info->alias),
		get_node_index(info->alias, node_check_starts(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set.alias - is a fn sets alias to string
 *   parameter struct
 *-str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set.alias(info.t *info, char *str)
{
	char *p;

	p = locate-char(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (un.set.alias(info, str));

	un.set.alias(info, str);
	return (add.a.node_end(&(info->alias), str, 0) == NULL);
}

/**
 * p.alias - is a fn prints an alias string
 *-node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int p.alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = locate-char(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _m.alias - is a fn that is a mimics the alias builtin (man alias)
 *   Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _m.alias(info.t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			p.alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = locate-char(info->argv[i], '=');
		if (p)
			set.alias(info, info->argv[i]);
		else
			p.alias(node_check_starts(info->alias, info->argv[i], '='));
	}

	return (0);
}
