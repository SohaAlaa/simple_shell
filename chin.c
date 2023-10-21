#include "shell.h"

/**
 * test_char_delimeter - is a fn that test if current char in buffer is a chain delimiter
 * the parameter struct
 * buf: the char buffer
 * p: address of current position in buf
 * Return: 1 if chain delimiter, 0 otherwise
 */
int test_char_delimeter(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * cont_ch_Ch - is a fn that checks we should continue chaining based on last status
 * the parameter struct
 * buf: the char buffer
 * p: address of current position in buf
 * i: starting position in buf
 * len: length of buf
 *
 * Return: Void
 */
void cont_ch_Ch(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * rp_alias_to_token - is a fn that replaces an aliases in the tokenized string
 * the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rp_alias_to_token(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = begin_from_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p =  add_character_toSTR(node->str, '=');
		if (!p)
			return (0);
		p = double_the_string(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * rp_vairble_to_tokenstr - is a fn that replaces vars in the tokenized string
 * the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rp_vairble_to_tokenstr(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_compare_lexo(info->argv[i], "$?"))
		{
			str_rp(&(info->argv[i]),
				double_the_string(cloneCvrt(info->status, 10, 0)));
			continue;
		}
		if (!_compare_lexo(info->argv[i], "$$"))
		{
			str_rp(&(info->argv[i]),
				double_the_string(cloneCvrt(getpid(), 10, 0)));
			continue;
		}
		node = begin_from_prefix(info->env, &info->argv[i][1], '=');
		if (node)
		{
			str_rp(&(info->argv[i]),
				double_the_string( add_character_toSTR(node->str, '=') + 1));
			continue;
		}
		str_rp(&info->argv[i], double_the_string(""));

	}
	return (0);
}

/** 
 * str_rp - is a fn that replaces string
 * old: address of old string
 * new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int str_rp(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
