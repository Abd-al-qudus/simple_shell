#include "main.h"

/**
* _strlen - get the length of a string
*
* @str: string to iterate
*
* Return: string length
*/

int _strlen(char *str)
{
	int count;

	for (count = 0; *str != '\0'; count++)
		str++;
	return (count);
}

/**
* _strdup - duplicate a string to another
*
* @src: string to duplicate
*
* Return: pointer to the duplicate
*/

char *_strdup(char *src)
{
	char *dup;
	int i, count;

	i = _strlen(src);
	count = 0;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	while (count >= 0)
	{
		*(dup + count) = *(src + count);
		if (*(src + count) == '\0')
			break;
		count++;
	}
	return (dup);
}

/**
* _strcmp - compare strings
*
* @src1: first string
* @src2: second string
*
* Return: 0 on success and -1 otherwise
*/

int _strcmp(char *src1, char *src2)
{
	int i, comp, len1, len2;

	len1 = _strlen(src1);
	len2 = _strlen(src2);
	if (len1 != len2)
		return (-1);
	comp = 0;
	for (i = 0; src1[i] != '\0' && src2[i] != '\0'; i++)
	{
		if (src1[i] == src2[i])
			comp++;
		continue;
	}
	if (comp == len1 && comp == len2)
		return (0);
	else
		return (-1);
}


/**
* _strtok - tokenize string and return tokens
*
* @str: string to tokenize
* @delim: interval to break
*
* Return: tokens always
*/

char *_strtok(char *str, const char *delim)
{
	static char *static_str;
	int index, strlength, found;

	static_str = 0;
	index = 0;
	strlength = 0;
	found = 0;
	if (delim == 0 || (str == 0 && static_str == 0))
		return (0);
	if (str == 0)
		str = static_str;
	while (str[strlength])
		strlength++;
	for (index = 0; index < strlength; index++)
	{
		if (str[index] == delim[0])
		{
			found = 1;
			break;
		}
	}
	if (!found)
	{
		static_str = 0;
		return (str);
	}
	if (str[0] == delim[0])
	{
		static_str = (str + 1);
		return ((char *)delim);
	}
	str[index] = '\0';
	if ((str + index + 1) != 0)
		static_str = (str + index + 1);
	else
		static_str = 0;
	return (str);
}

/**
* _strcat - concatenates strings
*
* @str1: string 1
* @str2: string 2
*
* Return: pointer sto str1
*/

char *_strcat(char *str1, char *str2)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (str1[i] != '\0')
	{
		i++;
	}
	while (str2[j] != '\0')
	{
		str1[i] = str2[j];
		j++;
		i++;
	}

	str1[i] = '\0';
	return (str1);
}
