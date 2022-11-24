#include "main.h"
#define MAX_BUILT_IN 5
#define MAX_PATH_SIZE 512

/**
* get_arg_list_length - get the length of argv
* @argv: list to conpute length
* Return: num of argument
*/

int get_arg_list_length(char **argv)
{
	int count;

	count = 0;
	for (count = 0; argv[count] != NULL; count++)
		;
	return (count);
}

/**
* _atoi - converts a string to an integer.
* @s: input string.
* Return: integer.
*/

int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;
		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}

/**
* eval_built_in - check whether a command is built in
* @cmd: command to check
* @argl: argument vector
* environ: environment variables
* Return: 1 on success, -1 on failure
*/

int eval_built_in(char *cmd, char **argl, char **environ)
{
	char path_name[MAX_PATH_SIZE], exitArg[50], *exitPtr;
	int res, check, i, argc, ck;
	size_t path_size;
	char *built_in[MAX_BUILT_IN];

	res = -1;
	built_in[0] = "exit";
	built_in[1] = "cd";
	built_in[2] = "setenv";
	built_in[3] = "unsetenv";
	built_in[4] = "alias";
	path_size = MAX_PATH_SIZE;
	for (i = 0; i < MAX_BUILT_IN; i++)
	{
		check = _strcmp(cmd, built_in[i]);
		if (check == 0)
		{
			res = i;
			break;
		}
	}
	if (res == -1)
		return (-1);
	argc = get_arg_list_length(argl);
	ck = 1;
	switch (res)
	{
		case 0:
			if (argl[1] != NULL)
			{
				exitPtr = strcpy(exitArg, argl[1]);
				freeCmd(argl, argc);
				exitHandler(exitPtr);
			}
			freeCmd(argl, argc);
			exit(EXIT_FAILURE);
			break;
		case 1:
			ck = dirHandler(argl[1], environ, path_name, path_size);
			break;
		case 2:
			if (argc < 3 || argc > 3)
				_puts("Invalid number of arguments\n");
			else
				ck = setEnvHandler(argl[1], argl[2], 1);
			break;
		case 3:
			if (argc == 2)
				ck = unsetEnvHandler(argl[1]);
			else
				_puts("Invalid number of argument\n");
			break;
		default:
			return (-1);
	}
	return (ck);
}

/**
* exitHandler - handle exit with or without argument
* @arg: exit argument
* return: void
*/

void exitHandler(char *arg)
{
	if (!_atoi(arg))
		_puts("Invalid argument\n");
	else
		exit(_atoi(arg));
}


/**
* dirHandler - change the CWD and update the PWD variable
* @arg: arg to execute
* @environ: environment variable to generate path
* @path: array to store cwd name
* @size: size of path array
* return: int on success or failure
*/

int dirHandler(char *arg, char **environ, char *path, size_t size)
{
	char *sh_path, *wd;
	int ck;

	if (arg)
	{
		if (_strcmp(arg, "-") == 0)
		{
			wd = getcwd(path, size);
			sh_path = generate_env(environ, "OLDPWD");
			ck = chdir(sh_path);
			if (ck != DIR_SUCCESS)
			{
				free(sh_path);
				_puts("Permission denied\n");
				return (DIR_ERROR);
			}
			free(sh_path);
			setEnvHandler("OLDPWD", wd, 1);
			setEnvHandler("PWD", getcwd(path, size), 1);
		}
		else
		{
			wd = getcwd(path, size);
			ck = chdir(arg);
			if (ck != DIR_SUCCESS)
			{
				_puts("Permission denied\n");
				return (DIR_ERROR);
			}
			setEnvHandler("OLDPWD", wd, 1);
			setEnvHandler("PWD", getcwd(path, size), 1);
		}
	}
	else
	{
		sh_path = generate_env(environ, "HOME");
		wd = getcwd(path, size);
		ck = chdir(sh_path);
		if (ck != DIR_SUCCESS)
		{
			free(sh_path);
			_puts("Permission denied\n");
			return (DIR_ERROR);
		}
		free(sh_path);
		setEnvHandler("OLDPWD", wd, 1);
		setEnvHandler("PWD", getcwd(path, size), 1);
	}
	return (DIR_SUCCESS);
}
