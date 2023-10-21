#include "shell.h"

/**
 * length_of_LL - is a fn that determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t length_of_LL(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * arr_strs_of_L - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **arr_strs_of_L(list_t *head)
{
	list_t *node = head;
	size_t i = length_of_LL(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_return_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str =  copy_strings(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * prt_ele_L - is a fn that prints all elements of a list_t linked list
 * h: pointer to first node
 *
 * Return: size of list
 */
size_t prt_ele_L(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		prt_ip_string(cloneCvrt(h->num, 10, 0));
		wr_charC_out(':');
		wr_charC_out(' ');
		prt_ip_string(h->str ? h->str : "(nil)");
		prt_ip_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * begin_from_prefix - is a fn that returns node whose string starts with prefix
 * node: pointer to list head
 * prefix: string to match
 * c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *begin_from_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = _check_haystack(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * return_by_no - is a fn that gets the index of a node
 * head: pointer to list head
 * node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t return_by_no(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
