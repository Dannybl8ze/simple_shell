#include "shell.h"

/**
 * **split_str:this splits a string into words. Repeated delimiters are ignored
 *
 * @str: This is the input string.
 *
 * @x: this is the delimeter string.
 *
 * Return: Returns a pointer to an array of strings, or NULL on failure
 */

char **split_str(char *str, char *x)
{
	int a, b, c, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!x)
		x = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!its_delimeter(str[a], x) && (its_delimeter(str[a + 1], x) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (its_delimeter(str[a], x))
			a++;
		c = 0;
		while (!its_delimeter(str[a + c], x) && str[a + c])
			c++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			s[b][n] = str[a++];
		s[b][n] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **split_str2: this splits a string into words.
 *
 * @str: this is the input string.
 *
 * @x: this is the delimeter.
 *
 * Return: Returns a pointer to an array of strings, or NULL on failure
 */
char **split_str2(char *str, char x)
{
	int a, b, c, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != x && str[a + 1] == x) ||
		    (str[a] != x && !str[a + 1]) || str[a + 1] == x)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == x && str[a] != x)
			a++;
		c = 0;
		while (str[a + c] != x && str[a + c] && str[a + c] != x)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			s[b][n] = str[a++];
		s[b][n] = 0;
	}
	s[b] = NULL;
	return (s);
}
