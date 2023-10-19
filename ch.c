#include "shell.h"

/**
 * is.ch -is a fn that tests if current char in bufffer is a chain delimeter
 *   the parameter struct
 *-buff: the char bufffer
 *-p: address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is.ch(info.t *info, char *buff, size_t *p)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check.ch - fn that checks we should continue chaining based on last status
 *   the parameter struct
 *-buff: the char bufffer
 *-p: address of current position in buff
 *-i: starting position in buff
 *-len: lengths of buff
 *
 * Return: Void
 */
void check.ch(info.t *info, char *buff, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * rp.alias -a fn that replaces an aliases in the tokenized string
 *   the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rp.alias(info.t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_check_starts(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = locate-char(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * rp.vars - is a fn that replaces vars in the tokenized string
 *   the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rp.vars(info.t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!strings_comparison(info->argv[i], "$?"))
		{
			rp.string(&(info->argv[i]),
				_strdup(cvrt_no(info->status, 10, 0)));
			continue;
		}
		if (!strings_comparison(info->argv[i], "$$"))
		{
			rp.string(&(info->argv[i]),
				_strdup(cvrt_no(getpid(), 10, 0)));
			continue;
		}
		node = node_check_starts(info->ev, &info->argv[i][1], '=');
		if (node)
		{
			rp.string(&(info->argv[i]),
				_strdup(locate-char(node->str, '=') + 1));
			continue;
		}
		rp.string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * rp.string - is a fn that replaces string
 *-old: address of old string
 *-new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rp.string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
