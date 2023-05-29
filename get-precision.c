#include "main.h"

/**
 * get_precision - calculates precision that will be printed
 * @format: Formatted strings to print arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int win_i = *i + 1;
	int precision = -1;

	if (format[win_i] != '.')
		return (precision);

	precision = 0;

	for (win_i += 1; format[win_i] != '\0'; win_i++)
	{
		if (is_digit(format[win_i]))
		{
			precision *= 10;
			precision += format[win_i] - '0';
		}
		else if (format[win_i] == '*')
		{
			win_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = win_i - 1;

	return (precision);
}
