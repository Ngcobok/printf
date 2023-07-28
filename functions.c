#include "main.h"

/************************* PROGRAME PRINT CHAR *************************/

/**
 * print_char - Programe that Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Programe Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, o;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (o = width - length; o > 0; o--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (o = width - length; o > 0; o--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Programe that Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Programe that Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int o = BUFF_SIZE - 2;
	int is_negative = 0;
	long int k = va_arg(types, long int);
	unsigned long int num;

	k = convert_size_number(k, size);

	if (k == 0)
		buffer[o--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)k;

	if (k < 0)
	{
		num = (unsigned long int)((-1) * k);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[o--] = (num % 10) + '0';
		num /= 10;
	}

	o++;

	return (write_number(is_negative, o, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Programe tht prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int k, l, o, sum;
	unsigned int c[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	k = va_arg(types, unsigned int);
	l = 2147483648; /* (2 ^ 31) */
	c[0] = k / l;
	for (o = 1; o < 32; i++)
	{
		l /= 2;
		c[o] = (k / l) % 2;
	}
	for (o = 0, sum = 0, count = 0; o < 32; i++)
	{
		sum += c[o];
		if (sum || o == 31)
		{
			char z = '0' + c[o];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
