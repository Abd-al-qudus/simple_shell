#include "main.h"

/**
* setEnvHandler - set environment variables with name and value
* @name: environment variable name
* @value: environ variable values
* @overwrite: overwrite environment variable
* Return: int on success and failure
*/

int setEnvHandler(char *name, char *value, int overwrite)
{
	int resp;
	if (overwrite)
		resp = setenv(name, value, overwrite);
	else
		resp = setenv(name, value, 0);
	return (resp);
}

/**
* unsetEnvHandler - unset environment variable
*
* @name: variable to unset
*
* Return: int on success or failure
*/

int unsetEnvHandler(char *name)
{
	int resp;

	resp = unsetenv(name);
	return (resp);
}
