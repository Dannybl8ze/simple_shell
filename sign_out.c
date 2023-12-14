#include "shell.h"

/**
 * *_strncpy: copies a string
 *
 * @dest: the destination string to be copied to
 *
 * @src: the source string.
 *
 * @m: the amount of characters to be copied.
 *
 * Return: returns the concatenated string
 */
char *_strncpy(char *dest, char *src, int m)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < m - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < m)
	{
		b = a;
		while (b < m)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 * _strncat: this concatenates two strings.
 *
 * @dest: the first string.
 *
 * @src: the second string.
 *
 * @m: the amount of bytes to be maximally used.
 *
 * Return: returns the concatenated string
 */
char *_strncat(char *dest, char *src, int m)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < m)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < m)
		dest[a] = '\0';
	return (s);
}

/**
 * _strchr: this locates a character in a string.
 *
 * @s: the string to be parsed.
 *
 * @c: the character to look for.
 *
 * Return: (s) a pointer to the memory area s.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
