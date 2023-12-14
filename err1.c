#include "shell.h"

/**
 * err_converter: this converts a string to an integer.
 *
 * @z: this is the string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int err_converter(char *z)
{
	int j = 0;
	unsigned long int result = 0;

	if (*z == '+')
		z++;  /* TODO: why does this make main return 255? */
	for (j = 0;  z[j] != '\0'; j++)
	{
		if (z[j] >= '0' && z[j] <= '9')
		{
			result *= 10;
			result += (z[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * errorPrinter: this prints an error message.
 *
 * @info: thi is the parameter and return information structure.
 *
 * @estr: this is the string containing specified error type.
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error.
 */
void errorPrinted(info_t *info, char *estr)
{
	e_puts(info->fname);
	e_puts(": ");
	dPrinter(info->line_count, STDERR_FILENO);
	e_puts(": ");
	e_puts(info->argv[0]);
	e_puts(": ");
	e_puts(estr);
}

/**
 * dPrinter: function to print a decimal (integer) number (base 10).
 *
 * @input: this is the input.
 *
 * @fd: this is the file-descriptor to write to.
 *
 * Return: returns a number of characters printed.
 */
int dPrinter(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = e_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * numberConverter: this is a converter function, a clone of itoa.
 *
 * @num: A number.
 *
 * @base: the base.
 *
 * @flags: flags arguement.
 *
 * Return: returns a string
 */
char *numberConverter(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * commentsOmitter: function replaces first instance of '#' with '\0'.
 *
 * @buf: the address of the string to be modified.
 *
 * Return: Always returns 0;
 */
void commentsOmitter(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
