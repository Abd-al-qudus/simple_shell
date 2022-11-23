#include <unistd.h>

/**
* _putchar - write single char to stdout
*
* @c: char to write
*
* Return: char to stdout
*/

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
* _puts - prints string to stdout
*
* @str: string to print
*
* Return: void
*/

void _puts(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
