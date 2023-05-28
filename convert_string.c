#include "main.h"

/**
 * convert - Converts a given number and a base to a string.
 * @num: The input number to be converted.
 * @base: The input base of the number.
 * @lowercase: A flag determines if hexa values will be in lowercase
 * Return: Returns pointer address.
 */

char *convert(unsigned long int num, int base, int lowercase)
{
	static char buffer[50];
	char *ptr = &buffer[49];
	const char *rep = (lowercase) ? "0123456789abcdef" : "0123456789ABCDEF";

	*ptr = '\0';
	while (num != 0)
	{
		*--ptr = rep[num % base];
		num /= base;
	}
	return (ptr);
}
