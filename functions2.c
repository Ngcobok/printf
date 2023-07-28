#include "main.h"

/******************PROGRAME PRINTS POINTER ******************/
/**
 * print_pointer - Programe that prints the value of a pointer variable
 * @types: List a of all arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: get the width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int okn = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[okn--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	okn++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PROGRAME PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Programe that prints ascii codes in hexa
 * of non printable chars
 * @types: Lista of all arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: get the width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int o = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[o] != '\0')
	{
		if (is_printable(str[i]))
			buffer[o + offset] = str[o];
		else
			offset += append_hexa_code(str[o], buffer, o + offset);

		o++;
	}

	buffer[o + offset] = '\0';

	return (write(1, buffer, o + offset));
}

/************************* PROGRAME PRINT REVERSE *************************/
/**
 * print_reverse - Programe that prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: get the width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int o, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (o = 0; str[i]; i++)
		;

	for (o = o - 1; o >= 0; o--)
	{
		char z = str[o];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PROGRAME PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Programe that print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: get the width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int o, k;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (o = 0; str[o]; o++)
	{
		for (o = 0; in[o]; o++)
		{
			if (in[k] == str[k])
			{
				x = out[k];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[k])
		{
			x = str[o];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
