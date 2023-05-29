#include "main.h"

/**
 * is_printable - Evaluates a char that is printable
 * @c: Char evaluation.
 * Return: one if c is printable or zero otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append asci hexadecimal code to buffer
 * @buffer: Array of characters.
 * @i: Index to start appending.
 * @ascii_code: ASCI CODE.
 * Return: Always three
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always two digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a character is an integer.
 * @c: Character of evaluation
 * Return: one if c is an integer or zero otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts num to the specific size
 * @num: The number to be casted.
 * @size: The number indicating the datatype to be casted.
 * Return: The casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a num to the specific size
 * @num: The number to be casted
 * @size: The number indicating the datatype to be casted
 * Return: The casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
