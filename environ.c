#include "main.h"

/**
* scan_env - set and search for the current path
*
* @environ: variable to check
*
* Return: linked list of env
*/
/*
list_t *scan_env(char **environ)
{
	list_t *head;
	char *tok, *sev, *cp, *com, *envg, *path, *token;
	int i, j, k, true;

	com = "PATH", token = "=", path = ":";
	for (i = 0, j = 0, k = 0; environ[i] != NULL; i++)
	{
		sev = _strdup(environ[i]);
		cp = _strtok(sev, token);
		true = _strcmp(com, cp);
		if (true == 0)
		{
			j = i;
			break;
		}
		continue;
	}
	envg = environ[j];
	i = _strlen(envg), j = _strlen(com);
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
	tok = strtok(envg, path);
	head = NULL;
	while (tok != NULL)
	{
		add_node_end(&head, tok);
		tok = strtok(NULL, path);
	}
	return (head);
}
*/
/**
* add_node_end - adds a new node at the end
* of a list_t list.
* @head: head of the linked list.
* @str: string to store in the list.
* Return: address of the head.
*/
/*
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new_h, *temp;

	new_h = malloc(sizeof(list_t));
	if (new_h == NULL)
		return (NULL);

	new_h->path = strdup(str);
	new_h->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_h;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_h;
	}

	return (*head);
}
*/
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
 * free_list - frees a list
 * @head: head of the linked list.
 * Return: no return.
 */
/*
void free_path(list_t *head)
{
	list_t *current;

	while ((current = head) != NULL)
	{
		head = head->next;
		free(current->path);
		free(current);
	}
}
*/
/**
* generate_env - return the environment
*
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
*
* @environ: env var to manipulate
*
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
		/*free(tosave);*/
		tosave = strtok(NULL, ":");
		i++;
	}
	env[i][0] = '\0';
	free(get_tok);
	free(tosave);
}
