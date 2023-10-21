#include "shell.h"

/**
 * prt_current_environ - prints the current environment
 * info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int prt_current_environ(info_t *info)
{
	prt_only_string_LL(info->env);
	return (0);
}

/**
 * get_valu_envir - gets the value of an environ variable
 * info: Structure containing potential arguments. Used to maintain
 * name: env var name
 *
 * Return: the value
 */
char *get_valu_envir(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = _check_haystack(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 *init_new_envir_var - is a fn that Initialize a new environment variable,
 *             or modify an existing one
 * info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
intinit_new_envir_var(info_t *info)
{
	if (info->argc != 3)
	{
		_prt_ip_str("Incorrect number of arguements\n");
		return (1);
	}
	if (_init_new_env_var(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * rm_envir_var - is a fn that Remove an environment variable
 * info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int rm_envir_var(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_prt_ip_str("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		rm_env_var(info, info->argv[i]);

	return (0);
}

/**
 * pop_env_LL - is a fn that populates env linked list
 * info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int pop_env_LL(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		end_L(&node, environ[i], 0);
	info->env = node;
	return (0);
}
