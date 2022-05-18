#include "main.h"
#include <stdlib.h>
/**
 * bin_digits -return number of digits
 * @n: number input
 *
 * Return: number of bin digits
 */
int bin_digits(unsigned int n)
{
	int count;

	count = 1;
	if (n == 0)
		return (1);
	while (n % 2 != 1)
	{
		count++;
		n = n / 2;
	}
	return (count);
}
/**
 * print_bin - print bin number
 * @n: input num
 */
void print_bin(unsigned int n)
{
	if (n == 0)
		_putchar('0');
	else if (n % 2 == 1 && n / 2 == 0)
		_putchar(1 + '0');
	else
	{
		print_bin(n / 2);
		_putchar((n % 2) + '0');
	}
}
/**
 * print_b - print and retrun number of digits of bin numbers
 * @ls: arg list item
 *
 * Return: number of bin digits printed
 */
int print_b(const va_list ls)
{
	unsigned int n;

	n = va_arg(ls, unsigned int);
	print_bin(n);
	return (bin_digits(n));
}
