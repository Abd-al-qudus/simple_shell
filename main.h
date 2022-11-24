#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define SETENV_SUCCESS 0
#define SETENV_ERROR 1
#define UNSETENV_SUCCESS 0
#define UNSETENV_ERROR 1
#define DIR_SUCCESS 0
#define DIR_ERROR 1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int checkLogical(char **argToken, char **environ, char path[15][15]);
int executeMultiCommand(char **argv, char **environ, char path[15][15]);
char **checkDelim(char *buffer, const char *delim);
void freeCmd(char **cmdArray, int len);
void _puts(char *s);
int dirHandler(char *arg, char **environ, char *path, size_t size);
void exitHandler(char *arg);
int unsetEnvHandler(char *name);
int setEnvHandler(char *name, char *value, int overwrite);
void sigintHandler(int sigint);
void sigstpHandler(int sigstp);
void path_vars(char env[15][15], char **environ);
char *generate_env(char **environ, char *env);
void remove_end_of_line(char *line);
void print_current_dir(char *dir);
int _strlen(char *arr);
int _putchar(char c);
char *scan_list(char [15][15],char *buffer);
int _getline(char *buffer, size_t size, FILE *stream);
char *_strtok(char *str, const char *delim);
char *_strdup(char *src);
char *_strcat(char *str1, char *str2);
int _strcmp(char *src1, char *scr2);
int execute(char **environ, char *buffer, char **av);
void generate_argv(char *param, char **argv);
int eval_built_in(char *cmd, char **argl, char **environ);
int get_arg_list_length(char **argv);
int _atoi(char *s);
char *get_dir(void);

#endif
