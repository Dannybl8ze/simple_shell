#include "shell.h"

/**
 * collect_record: this gets the history file.
 *
 * @info: parameter and information structure.
 *
 * Return: returns allocated string containg history file.
 */

char *collect_record(info_t *info)
{
	char *buf, *dir;

	dir = selectEnv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_str(buf, dir);
	catStr(buf, "/");
	catStr(buf, HIST_FILE);
	return (buf);
}

/**
 * write_record: this creates a file, or appends to an existing file.
 *
 * @info: the parameter and information structure.
 *
 * Return: returns 1 on success, else -1.
 */
int write_record(info_t *info)
{
	ssize_t fd;
	char *filename = collect_record(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_record: this reads history from file.
 *
 * @info: the parameter and information structure
 *
 * Return:returns histcount on success, 0 otherwise
 */
int read_record(info_t *info)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = collect_record(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			create_record_list(info, buf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		create_record_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_indexNode(&(info->history), 0);
	record_renumber(info);
	return (info->histcount);
}

/**
 * create_record_list: this adds entry to a history linked list.
 *
 * @info:this is a Structure containing potential arguments. Used to maintain.
 *
 * @buf: this rep buffer.
 *
 * @linecount: this is the history linecount, histcount.
 *
 * Return: Always 0
 */
int create_record_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	increase_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * record_renumber: this renumbers the history linked list after changes.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: returns the new histcount
 */
int record_renumber(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
