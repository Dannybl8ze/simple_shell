#include "shell.h"

/**
 * chainTest: this tests if the current character in a buffer is a chain delimeter.
 *
 * @info: this gives the structure of the parameter.
 *
 * @buf: this represent the character buffer.
 *
 * @p: the address of the current position in buf.
 *
 * Return: returns 1 if chain delimeter, 0 otherwise.
 */
int chainTest(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';') /* this finds the end of this command */
	{
		buf[i] = 0; /* this replaces semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * chainCheck: this checks for continuous chaining based on the last status.
 *
 * @info: this gives the structure of the parameter.
 *
 * @buf: this represent the character buffer.
 *
 * @p: the address of the current position in buf.
 *
 * @a: the starting position in the buf.
 *
 * @len: the length of the buf.
 *
 * Return: returns Void
 */
void chainCheck(info_t *info, char *buf, size_t *p, size_t a, size_t len)
{
	size_t m = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[a] = 0;
			m = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[a] = 0;
			j = len;
		}
	}

	*p = m;
}

/**
 * change_alias: this replaces an aliases in the tokenized string.
 *
 * @info: this gives the structure of the parameter.
 *
 * Return: this returns 1 if replaced, 0 otherwise
 */
int change_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
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
 * chenge_variants: replaces variables in the tokenized string.
 *
 * @info: this gives the structure of the parameter.
 *
 * Return: this returns 1 if replaced, 0 otherwise
 */
int change_variants(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			replace_string(&(info->argv[a]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces a string.
 *
 * @old: this rep address of old string.
 *
 * @new: this rep new string.
 *
 * Return: this returns 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
