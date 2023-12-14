#include "shell.h"

/**
 * _interact: this returns a true if shell is in interactive mode.
 * @info: structure of an address
 *
 * Return: returns 1 if it is in interactive mode, 0 otherwise
 */
int _interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * its_delimeter: this checks if a character is a delimeter.
 * @b: this is the character to check.
 * @delim: this the delimeter string.
 *
 * Return: returns 1 if it is true, 0 if it is false
 */
int its_delimeter(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 *its_alphabs - checks for alphabetic character.
 *
 *@b: This is the character to input.
 *
 *Return: returns 1 if b is alphabetic, 0 otherwise
 */

int its_alphabs(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_converter: this converts a string to an integer.
 *
 *@s: this is the string to be converted.
 *
 *Return: returns 0 if there are no numbers in string, converted number otherwise
 */

int _converter(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0;  s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
