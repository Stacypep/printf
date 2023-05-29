#include "main.h"

/**
 * handle_ write_ char - Printing of a string
 * @c: character datatypes.
 * @buffer: Buffer array for handle printing
 * @flags: Calculation of active flags.
 * @width: get width.
 * @precision: For precision specifier
 * @size: For the size specifier
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* character is stored at left and paddind at buffer's right */
	int x = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pad = '0';

	buffer[x++] = c;
	buffer[x] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (x = 0; x < width - 1; x++)
			buffer[BUFF_SIZE - x - 2] = pad;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - x - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - x - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}


/**
 * write_number - For printing a string
 * @is_negative: Listing of arguments
 * @ind: character datatypes.
 * @buffer: Buffer array for handling print
 * @flags:  Calculation of active flags
 * @width: get width ...
 * @precision: The precision specifier
 * @size: The size specifier
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char pad = ' ', extra = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		extra = '-';
	else if (flags & F_PLUS)
		extra = '+';
	else if (flags & F_SPACE)
		extra = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, pad, extra));
}

/**
 * write_num - Writes a formatted number to the output.
 * @ind: Index to the number that starts on the buffer
 * @buffer: Buffer of an array
 * @flags: Calculation of active flags
 * @width: get width
 * @prec: The precision specifier
 * @length: Num length
 * @padd: The pading character
 * @extra_c: Extra character
 * Return: Number of printed character.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int x, pad = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no character is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displaying with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (x = 1; x < width - length + 1; x++)
			buffer[x] = padd;
		buffer[x] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], x - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], x - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--pad] = extra_c;
			return (write(1, &buffer[pad], x - pad) +
				write(1, &buffer[ind], length - (1 - pad)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned num
 * @is_negative: The number indicating that num is negative
 * @ind: Index of the num that starts in the buffer
 * @buffer: Array of characters
 * @flags: The flags specifiers
 * @width: The width specifier
 * @precision: The precision specifier
 * @size: The size specifier
 * Return: Number of written characters.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, x = 0;
	char pad = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no character is printed */

	if (precision > 0 && precision < length)
		pad = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > length)
	{
		for (x = 0; x < width - length; x++)
			buffer[x] = pad;

		buffer[x] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], x));
		}
		else /* Asign an extra character to the left of pading [pad>buffer]*/
		{
			return (write(1, &buffer[0], x) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write to a memory address
 * @buffer: Arrays of characters
 * @ind: Index to the number that starts in the buffer
 * @length: The length of num
 * @width: The width specifier
 * @flags: The flags specifier
 * @padd: Character that represents the pading
 * @extra_c: Character representing extra character
 * @padd_start: Index that padding should start
 * Return: Number of written characters.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int a;

	if (width > length)
	{
		for (a = 3; a < width - length + 3; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], a - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
