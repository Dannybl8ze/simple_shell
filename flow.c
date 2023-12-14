#include "shell.h"

/**
 * str_len: this returns the length of a string.
 *
 * @z: this is the string's length to check.
 *
 * Return: returns an integer length of string.
 */
int str_len(char *z)
{
	int j = 0;

	if (!z)
		return (0);

	while (*z++)
		j++;
	return (j);
}

/**
 * cmp_str: this  performs lexicogarphic comparison of two strangs.
 *
 * @z1: this is the first string.
 *
 * @z2: this is 7the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int cmp_str(char *z1, char *z2)
{
	while (*z1 && *z2)
	{
		if (*z1 != *z2)
			return (*z1 - *z2);
		z1++;
		z2++;
	}
	if (*z1 == *z2)
		return (0);
	else
		return (*z1 < *z2 ? -1 : 1);
}

/**
 * startWith: this  checks if needle starts with haystack.
 *
 * @haystack: A string to search.
 *
 * @needle: A the substring to find.
 *
 * Return: returns an address of next char of haystack or NULL.
 */
char *startWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * catStr: this concatenates two strings.
 *
 * @dest: this is the destination buffer.
 *
 * @src: this is  the source buffer.
 *
 * Return: rrturns a pointer to destination buffer.
 */
char *catStr(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
