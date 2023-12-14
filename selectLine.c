#include "shell.h"

/**
 * bufInput: this buffers chained commands.
 *
 * @info: the parameter struct.
 *
 * @buf: the address of buffer.
 *
 * @len: the address of length variable.
 *
 * Return: returns bytes read
 */
ssize_t bufInput(info_t *info, char **buf, size_t *len)
{
	ssize_t q = 0;
	size_t len_p = 0;

	if (!*len) /* if there be nothing left in the buffer, then fill it */
	{
		/*free_b((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _handlesigint);
#if USE_GETLINE
		q = selectLine(buf, &len_p, stdin);
#else
		q = _selectLine(info, buf, &len_p);
#endif
		if (q > 0)
		{
			if ((*buf)[q - 1] == '\n')
			{
				(*buf)[q - 1] = '\0'; /* this removes trailing newline */
				q--;
			}
			info->linecount_flag = 1;
			commentsOmitter(*buf);
			create_record_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = q;
				info->cmd_buf = buf;
			}
		}
	}
	return (q);
}

/**
 * select_input: this gets a line minus the newline.
 *
 * @info: the parameter struct.
 *
 * Return: bytes read
 */
ssize_t select_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, b, len;
	ssize_t q = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	q = bufInput(info, &buf, &len);
	if (q == -1) /* EOF */
		return (-1);
	if (len) /* showing we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		p = buf + a; /* this get pointer for return */

		chainCheck(info, buf, &b, a, len);
		while (b < len) /* this iterate to semicolon or end */
		{
			if (chainTest(info, buf, &b))
				break;
			b++;
		}

		a = b + 1; /* the increment past nulled ';'' */
		if (a >= len) /* it reached end of buffer? */
		{
			a = len = 0; /* this resets position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* this passes back pointer to current command position */
		return (str_len(p)); /* this returns length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _selectLine() */
	return (q); /* return length of buffer from _selectLine() */
}

/**
 * _bufread: reads a buffer.
 *
 * @info: the parameter struct.
 *
 * @buf: the buffer.
 *
 * @a: size
 *
 * Return: returns q
 */
ssize_t _bufread(info_t *info, char *buf, size_t *a)
{
	ssize_t q = 0;

	if (*a)
		return (0);
	q = read(info->readfd, buf, READ_BUF_SIZE);
	if (q >= 0)
		*a = q;
	return (q);
}

/**
 * _selectLine: this gets the next line of input from STDIN.
 *
 * @info: the parameter struct.
 *
 * @ptr: a address of pointer to buffer, preallocated or NULL.
 *
 * @length: the size of preallocated ptr buffer if not NULL.
 *
 * Return: s
 */
int _selectLine(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	q = _bufread(info, buf, &len);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, k - a);
	else
		_strncpy(new_p, buf + a, k - a + 1);

	s += k - a;
	a = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * _handlesigint:  the blocks ctrl-C.
 *
 * @sig_num: the signal number
 *
 * Return: void
 */
void _handlesigint(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
