#include "shell.h"

/**
 * copy_str: this copys a string.
 *
 * @dest: this is the destination.
 *
 * @src: this is the source.
 *
 * Return: pointer to destination.
 */
char *copy_str(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * dup_str: this duplicates a string.
 *
 * @str: this is the string to duplicate.
 *
 * Return: returns pointer to the duplicated string.
 */
char *dup_str(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts: this prints an input string.
 *
 *@str: this is the string to be printed.
 *
 * Return: Returns Nothing.
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar:this writes the character a to stdout.
 *
 * @a: The character to be printed.
 *
 * Return: On success 1 is returned.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char a)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (a != BUF_FLUSH)
		buf[j++] = a;
	return (1);
}
