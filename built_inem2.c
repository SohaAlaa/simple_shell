#include "shell.h"

/**
 * display_H_list - is a fn that displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 *Struct containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int display_H_list(info_t *info)
{
	prt_ele_L(info->history);
	return (0);
}

/**
 * unset_alias_toStr -is a fn that  unsets alias to string
 * parameter struct
 * string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias_toStr(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p =  add_character_toSTR(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delnode_of_no(&(info->alias),
		return_by_no(info->alias, begin_from_prefix(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias_toStr - is a fn that sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias_toStr(info_t *info, char *str)
{
	char *p;

	p =  add_character_toSTR(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias_toStr(info, str));

	unset_alias_toStr(info, str);
	return (end_L(&(info->alias), str, 0) == NULL);
}

/**
 * prt_str_alias - is a fn that prints an alias string
 * alias node is node
 * Return: Always 0 on success, 1 on error
 */
int prt_str_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p =  add_character_toSTR(node->str, '=');
		for (a = node->str; a <= p; a++)
			wr_charC_out(*a);
		wr_charC_out('\'');
		prt_ip_string(p + 1);
		prt_ip_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * symbol_alias - is a fn that mimics the alias builtin (man alias)
 * Struct containing potential arguments. Used to maintain
 *         constant function prototype.
 *  Return: Always 0
 */
int symbol_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			prt_str_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p =  add_character_toSTR(info->argv[i], '=');
		if (p)
			set_alias_toStr(info, info->argv[i]);
		else
			prt_str_alias(begin_from_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}
