#include "main.h"
/**
* _power  - return power of x to y
* @x: base
* @y: exponent
* Return: x raised to y
*/
size_t  _power(size_t x, size_t y)
{
	size_t mul = 1;

	while (y)
	{
		mul = x * mul;
		y--;
	}
	return (mul);
}
/**
* _atoi - return first numeric part of string s
* @s: string to be parsed
* Return: numeric representation of part or all of string
*/
size_t _atoi(char *s)
{
	size_t sum = 0, i = 0;
	int len = 0;

	while (s[len])
	{
		if (s[len] < '0' || s[len]  > '9')
			break;
		len++;
	}

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			break;
		sum = sum + (s[i] - '0') * _power(10, len - i - 1);
		i++;
	}
	return (sum);
}
