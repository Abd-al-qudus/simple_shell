#include "main.h"
#define MAX_ARGV_SIZE 20
#define MAX_BUFFER_SIZE 4096


/**
* main - call other function
* @environ: env variables
* Return: Always 0
*/

int main(int ac __attribute__((unused)), char **av  __attribute__((unused)), char **environ)
{
	char buffer[MAX_BUFFER_SIZE], path[15][15];
	size_t buf_size;
	int check, flag, newp;
	char **agv;

	signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigstpHandler);
	buf_size = MAX_BUFFER_SIZE, flag = 1;
	path_vars(path, environ);
	while (1)
	{
		_putchar('$');
		_putchar(' ');
		flag = _getline(buffer, buf_size, stdin);
		if (flag == 0)
			exit(0);
		remove_end_of_line(buffer);
		if (*buffer == '\0')
			continue;
		agv = checkDelim(buffer, ";");
		check = eval_built_in(buffer, agv, environ);
		if (check == -1)
		{
			newp = checkLogical(agv, environ, path);
			if (newp != -1)
				newp = 0;
			freeCmd(agv, get_arg_list_length(agv));
		}
	}
	return (0);
}


/**
* execute - execute a process
* @environ: environment variables
* @buffer: memory
* @av: argument vector
* Return: 0 on success, errno is set
*/

int execute(char **environ, char *buffer, char **av)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
		exit(0);
	else if (child_pid == 0)
	{
		int run_cmd;

		run_cmd = execve(buffer, av, environ);
		if (run_cmd == -1)
		{
			_puts(av[0]);
			_puts(": execution failed\n");
			exit(run_cmd);
		}
	}
	wait(NULL);
	return (0);
}

/**
* sigintHandler - handle termination signal
* @sigint: signal to handle
* Return: void
*/

void sigintHandler(int sigint)
{
	if (sigint)
	{
		signal(SIGINT, sigintHandler);
		_putchar('\n');
		_putchar('$');
		_putchar(' ');
		fflush(stdout);
	}
}

/**
* sigstpHandler - handle suspension signal
* @sigstp: signal to handle
* Return: void
*/

void sigstpHandler(int sigstp)
{
	if (sigstp)
		exit(0);
}
