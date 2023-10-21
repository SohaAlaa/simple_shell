#include "shell.h"

/**
 * return_str_array - is a fn that returns the string array copy of our environ
 * info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **return_str_array(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = arr_strs_of_L(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * rm_env_var - is a fn that Remove an environment variable
 * info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * var: the string env var property
 */
int rm_env_var(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _check_haystack(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delnode_of_no(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _init_new_env_var - is a fn that Initialize a new environment variable,
 *             or modify an existing one
 * info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * var: the string env var property
 * value: the string env var value
 *  Return: Always 0
 */
int _init_new_env_var(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_return_length(var) + _return_length(value) + 2);
	if (!buf)
		return (1);
	 copy_strings(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = _check_haystack(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	end_L(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
