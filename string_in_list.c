#include "shell.h"

/**
 * start_a_L - is a fn that adds a node to the start of the list
 * head: address of pointer to head node
 * str: str field of node
 * num: node index used by history
 *
 * Return: size of list
 */
list_t *start_a_L(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	fill_wt_const((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = double_the_string(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * end_L - is a fn that adds a node to the end of the list
 * head: address of pointer to head node
 * str: str field of node
 * num: node index used by history
 *
 * Return: size of list
 */
list_t *end_L(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	fill_wt_const((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = double_the_string(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * prt_only_string_LL - is a fn that prints only the str element of a list_t linked list
 * h: pointer to first node
 *
 * Return: size of list
 */
size_t prt_only_string_LL(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		prt_ip_string(h->str ? h->str : "(nil)");
		prt_ip_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delnode_of_no - is a fn that deletes node at given index
 * head: address of pointer to first node
 * index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delnode_of_no(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * letgo_all_nodes - is a fn that frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void letgo_all_nodes(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
