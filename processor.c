#include "shell.h"

/**
 * exec_cmd: this determines whether a file is an executable command.
 *
 * @info: the information and parameter struct.
 *
 * @path: this is the path to the file.
 *
 * Return: returns 1 if true, 0 otherwise.
 */
int exec_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _charsdup: this duplicates characters.
 *
 * @pathstr: this is the PATH yo the string.
 *
 * @start: this starts the index.
 *
 * @stop: this stops the index.
 *
 * Return: returns a pointer to new buffer.
 */
char *_charsdup(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, c = 0;

	for (c = 0, a = start; a < stop; a++)
		if (pathstr[i] != ':')
			buf[c++] = pathstr[a];
	buf[c] = 0;
	return (buf);
}

/**
 * _pathlook: this finds this cmd in the PATH string.
 *
 * @info:this is the information and parameter struct.
 *
 * @pathstr: this is the PATH string.
 *
 * @cmd: this is the cmd to find.
 *
 * Return: returns the full path of cmd if found or NULL
 */
char *_pathlook(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && startsWith(cmd, "./"))
	{
		if (exec_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = _charsdup(pathstr, curr_pos, a);
			if (!*path)
				catStr(path, cmd);
			else
			{
				catStr(path, "/");
				catStr(path, cmd);
			}
			if (exec_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
