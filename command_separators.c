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
*
* @cmdArray: command array
*
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
	int count, i;

	count = get_arg_list_length(argv);
	for (i = 0; i < count; i++)
	{
		tokenArgs = checkDelim(argv[i], " ");
		env = scan_list(path, tokenArgs[0]);
		if (env == NULL)
		{
			_puts(tokenArgs[0]);
			_puts(": No such command\n");
			freeCmd(tokenArgs, get_arg_list_length(tokenArgs));
			free(env);
		}
		else
		{
			execute(environ, env, tokenArgs);
			freeCmd(tokenArgs, get_arg_list_length(tokenArgs));
			free(env);
		}

	}
	return (count);
}
