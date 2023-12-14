#include "shell.h"

/**
 * myEnv: this prints the current environment.
 *
 * @info: Structure containing potential arguments, used to maintain
 *          constant function prototype.
 * Return: this Always returns 0.
 */
int myEnv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * selectEnv: this selects the value of an environ variable.
 *
 * @info: Structure containing potential arguments. Used to maintain.
 *
 * @name: environ variable .name
 *
 * Return: returns the value
 */
char *selectEnv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * myset_env: this Initialize a new environment variable,
 *             or modify an existing one.
 *
 * @info: A Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always returns 0
 */
int myset_env(info_t *info)
{
	if (info->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myunset_env: this Removes a variable in an environment.
 *
 * @info: A Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always returns 0
 */
int myunset_env(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		unset_env(info, info->argv[j]);

	return (0);
}

/**
 * popenvList: this populates the environ linked list.
 *
 * @info: A Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always returns 0
 */
int popenvList(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
