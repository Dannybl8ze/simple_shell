#include "shell.h"

/**
 *e_puts: this prints an input of string.
 *
 * @str: this is the string to be printed.
 *
 * Return: returns Nothing
 */
void e_puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		e_putchar(str[j]);
		j++;
	}
}

/**
 * e_putchar: this writes the character a to stderr.
 *
 * @a: This is the character to be printed.
 *
 * Return: returns 1 on success.
 * and -1 is returned on error, and error is set appropriately.
 */
int e_putchar(char a)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (a != BUF_FLUSH)
		buf[j++] = a;
	return (1);
}

/**
 * put_fd: this writes the character a to the given fd.
 *
 * @a: The character to be printed.
 *
 * @fd: The file-descriptor to write to
 *
 * Return: returns 1 on success.
 * -1 is returned on error, and errno is set appropriately.
 */
int put_fd(char a, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (a != BUF_FLUSH)
		buf[j++] = a;
	return (1);
}

/**
 *puts_fd: this prints an input string.
 *
 * @str: this is the string to be printed.
 *
 * @fd: the file-descriptor to write to
 *
 * Return: returns the number of chars put
 */
int puts_fd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += put_fd(*str++, fd);
	}
	return (j);
}
