#include "main.h"

/**
* scan_list - scan all the elements of a list_t list.
* @h: singly linked list.
* @buffer: buffer to check
* Return: scan result of elements in the list.
*/

char *scan_list(char env[15][15], char *buffer)
{
	char *path;
	int check, verify;

	path = (char *)malloc(sizeof(char) * 50);
	if (path == NULL)
		return (NULL);
	verify = 0;
	if (buffer[0] == '/')
	{
		check = access(buffer, X_OK);
		if (check != 0)
		{
			free(path);
			return (NULL);
		}
		verify++;
		strcpy(path, buffer);
	}
	else
	{
		int i;

		for (i = 0; *env[i] != '\0'; i++)
		{
			strcpy(path, env[i]);
			_strcat(path, "/");
			_strcat(path, buffer);
			if (access(path, X_OK) == 0)
			{
				verify++;
				break;
			}
		}
	}
	if (verify == 0)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

/**
* generate_env - return the environment
* @env: environment variable to get
* @environ: environ - environment
* return: a pointer to the environment
*/

char *generate_env(char **environ, char *env)
{
	char  *sev, *cp, *envg, *token;
	int i, j, k, true;

	token = "=";
	envg = (char *)malloc(sizeof(char) * 256);
	for (i = 0, j = 0, k = 0; environ[i] != NULL; i++)
	{
		sev = _strdup(environ[i]);
		cp = _strtok(sev, token);
		true = _strcmp(env, cp);
		if (true == 0)
		{
			j = i;
			free(sev);
			break;
		}
		free(sev);
		continue;
	}
	strcpy(envg, environ[j]);
	i = _strlen(envg), j = _strlen(env);
	while (k <= j)
	{
		int a;

		for (a = 0; a < i - 1; a++)
		{
			*(envg + a) = *(envg + a + 1);
		}
		*(envg + a) = '\0';
		k++;
	}
	return (envg);
}

/**
* path_vars - environment vars
* @environ: env var to manipulate
* @env: path th store command
* Return: pointer to env array
*/

void path_vars(char env[15][15], char **environ)
{
	char *tosave, *get_tok;
	int i;

	i = 0;
	get_tok = generate_env(environ, "PATH");
	tosave = (char *)malloc(sizeof(char) * 128);
	tosave = strtok(get_tok, ":");
	while (tosave != NULL)
	{
		strcpy(env[i], tosave);
		tosave = strtok(NULL, ":");
		i++;
	}
	env[i][0] = '\0';
	free(get_tok);
	free(tosave);
}
