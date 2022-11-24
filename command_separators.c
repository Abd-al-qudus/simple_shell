#include "main.h"
#define MAX_CMD 1024
#define MAX_CMD_LEN 1024
/**
* checkSemiColon - check command for semi colon
* @cmd: input command
* @delim: token delimeter
* Return: arg list
*/

char **checkDelim(char *cmd, const char *delim)
{
	char **cmdList, *token;
	int i;

	cmdList = malloc(sizeof(char) * MAX_CMD);
	i = 0;
	token = strtok(cmd, delim);
	while (token != NULL)
	{
		int k, j;

		while (*token == ' ')
		{
			token++;
		}
		k = strlen(token);
		for (j = k - 1; j >= 0; j--)
		{
			if (token[j] != ' ')
				break;
		}
		token[j + 1] = '\0';
		cmdList[i] = malloc(sizeof(char) * MAX_CMD_LEN);
		strcpy(cmdList[i], token);
		i++;
		token = strtok(NULL, delim);
	}
	cmdList[i] = NULL;
	return (cmdList);
}

/**
* freeCmd - free command list array
* @cmdArray: command array
* Return: void
*/

void freeCmd(char **cmdArray, int len)
{
	int i;

	for (i = 0; i < len; i++)
		free(cmdArray[i]);
	free(cmdArray);
}

/**
* executeMultiCommand - execute multiple commands with ; separator
* @environ: environment variable for execution
* @argv: vector commands
* Return: int on success or failure
*/

int executeMultiCommand(char **argv, char **environ, char path[15][15])
{
	char **tokenArgs, *env;
	int i, cmd;

	cmd = 0, i = 0;
	for (i = 0; i < get_arg_list_length(argv); i++)
	{
		tokenArgs = checkDelim(argv[i], " ");
		printf("tk[0] %s\n", tokenArgs[0]);
		if (tokenArgs[i] == NULL)
			env = scan_list(path, strtok(tokenArgs[0], " "));
		else
			env = scan_list(path, tokenArgs[0]);
		if (env == NULL)
		{
			_puts(tokenArgs[0]);
			_puts(": No such command\n");
			freeCmd(tokenArgs, get_arg_list_length(tokenArgs));
			cmd = -1;
			return (cmd);
		}
		else
		{
			printf("[*] %s\n", env);
			cmd = execute(environ, env, tokenArgs);
			if (cmd == -1)
			{
				freeCmd(tokenArgs, get_arg_list_length(tokenArgs));
				free(env);
				return (cmd);
			}
			freeCmd(tokenArgs, get_arg_list_length(tokenArgs));
			free(env);
		}
	}
	return (cmd);
}

/**
* checkLogical - check logical operators
* @argToken: list of arguments
* @environ: environment variables
* @path: command path
* Return: sub token vector
*/

int checkLogical(char **argToken, char **environ, char path[15][15])
{
	char **orSubToken, **andSubToken;
	int i, k;

	for (k = 0; k < get_arg_list_length(argToken); k++)
	{
		orSubToken = checkDelim(argToken[k], "||");
		for (i = 0; i < get_arg_list_length(orSubToken); i++)
		{
			int cmd;

			andSubToken = checkDelim(orSubToken[i], "&&");
			cmd = executeMultiCommand(andSubToken, environ, path);
			if (cmd == -1)
			{
				;
			}
			freeCmd(andSubToken, get_arg_list_length(andSubToken));
		}
		freeCmd(orSubToken, get_arg_list_length(orSubToken));
	}
	return (k);
}
