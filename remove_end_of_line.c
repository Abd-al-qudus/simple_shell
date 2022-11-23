#include "main.h"

/**
* remove_end_of_line - remove the trailing spaces
*
* @line: input to remove trailing spaces
*
* Return: void
*/

void remove_end_of_line(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\n')
	{
		i++;
	}
	line[i] = '\0';
}
