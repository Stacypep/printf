#include "main.h"

/**
 * _printf - It produces output according to a format
 * @format: A format string containing the characters and the specifiers
 * Description: This function will call the get_print() function that will
 * determine which printing function to call depending on the conversion
 * specifiers contained into the format string
 * Return: The length of the formatted output string
 */
int _printf(const char *format, ...)
{
	int (*xfunc)(va_list, flags_t *);
	const char *x;
	va_list arguments;
	flags_t flags = {0, 0, 0};

	register int count = 0;

	va_start(arguments, format);
	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (x = format; *x; x++)
	{
		if (*x == '%')
		{
			x++;
			if (*x == '%')
			{
				count += _putchar('%');
				continue;
			}
			while (get_flag(*x, &flags))
				x++;
			xfunc = get_print(*x);
			count += (xfunc)
				? xfunc(arguments, &flags)
				OA
				: _printf("%%%c", *x);
		} else
			count += _putchar(*x);
	}
	_putchar(-1);
	va_end(arguments);
	return (count);
}
