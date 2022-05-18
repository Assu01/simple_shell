#include "shell.h"

/**
 * _atoi - turns a string into an integer
 * @s: string
 *
 * Return: integer
 */

int _atoi(char *s)
{
	unsigned int index, neg_counter, num;

	index = 0;
	neg_counter = 0;

	while (!(s[index] >= '0' && s[index] <= '9') && s[index] != '\0')
	{
		if (s[index] == '-')
			neg_counter++;

		index++;
	}

	num = 0;

	while (s[index] >= '0' && s[index] <= '9')
	{
		num = (s[index] - '0') + (num * 10);
		index++;
	}

	if (neg_counter % 2 != 0)
		num = -num;

	return (num);
}

/**
 * print_number - print an integer
 * @n: integer to print
 */

void print_number(int n)
{
	int digit, sum, last;
	int divis = 1000000000;
	unsigned int num;

	num = n;
	sum = 0;

	while (divis > 1)
	{
		digit = (num / divis) % 10;
		sum += digit;
		if (sum != 0)
			_putchar(digit + '0');
		divis = divis / 10;
	}

	last = num % 10;
	_putchar(last + '0');
}
