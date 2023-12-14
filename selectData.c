#include "shell.h"

/**
 * format_info: this initializes info_t struct.
 *
 * @info: the struct address.
 */
void format_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * arrange_info: this initializes info_t struct.
 *
 * @info: the struct address.
 *
 * @av: argument vector
 */
void arrange_info(info_t *info, char **av)
{
	int a = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		change_alias(info);
		change_variants(info);
	}
}

/**
 * freeInfo: this frees info_t struct fields.
 *
 * @info: the struct address.
 *
 * @all: true if freeing all fields.
 */
void freeInfo(info_t *info, int all)
{
	free_s(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		free_s(info->environ);
			info->environ = NULL;
		free_b((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
