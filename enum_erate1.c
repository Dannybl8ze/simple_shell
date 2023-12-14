#include "shell.h"

/**
 * listLen: this determines the length of a linked list.
 *
 * @h: A pointer to the first node.
 *
 * Return: returns the size of list.
 */
size_t listLen(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * stringsList: this returns an array of the strings of the list->str.
 *
 * @head: A pointer to the first node.
 *
 * Return: rrturns array of strings
 */
char **stringsList(list_t *head)
{
	list_t *node = head;
	size_t n = list_len(head), m;
	char **strs;
	char *str;

	if (!head || !n)
		return (NULL);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (m = 0; m < n; m++)
				free(strs[m]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[n] = str;
	}
	strs[n] = NULL;
	return (strs);
}


/**
 * listPrinter: this prints all the elements of a list_t linked list.
 *
 * @h: A pointer to the first node.
 *
 * Return: returns the size of list.
 */
size_t listPrinter(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * startsNode_with: this returns  node whose string starts with prefix
 *
 * @node: A pointer to the list head 
 *
 * @prefix: A string to match.
 *
 * @a: the next character after prefix to match
 *
 * Return: returns a match node or null
 */
list_t *startsNode_with(list_t *node, char *prefix, char a)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->str, prefix);
		if (p && ((a == -1) || (*p == a)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * select_nodeIndex: this selects the index of a node.
 *
 * @head: A pointer to the list head.
 *
 * @node: A pointer to the node.
 *
 * Return: returns the index of node or -1
 */
ssize_t select_nodeIndex(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}
