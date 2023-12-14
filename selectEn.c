#include "shell.h"

/**
 * select_environ: this returns the string array copy of our environ.
 *
 * @info: The structure containing potential arguments. Used to maintain constant function prototype.
 *
 * Return: Always returns 0.
 */
char **select_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_env: This Removes an environment variable.
 *
 * @info: TheStructure containing potential arguments. Used to maintain constant function prototype.
 *
 *  Return: ths returns 1 on delete, 0 otherwise.
 *
 * @var: the string env var property
 */
int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_indexNote(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * set_env: this Initialize a new environment variable, or modify an existing one.
 *
 * @info: This Structure containing potential arguments. Used to maintain constant function prototype.
 *
 * @var: the string env var property.
 *
 * @value: the string env var value
 *
 * Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	copy_str(buf, var);
	catStr(buf, "=");
	catStr(buf, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	increase_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
