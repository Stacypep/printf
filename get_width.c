#include "main.h"

/**
 * get_width - Calculates the width to be printed
 * @format: Formats a string to print the arguments.
 * @i: List of arguments for printing.
 * @list: The list of arguments.
 * Return: the width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr;
	int width = 0;

	for (curr = *i + 1; format[curr] != '\0'; curr++)
	{
		if (is_digit(format[curr]))
		{
			width *= 10;
			width += format[curr] - '0';
		}
		else if (format[curr] == '*')
		{
			curr++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr - 1;

	return (width);
}
