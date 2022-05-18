#ifndef _HEADER_
#define _HEADER_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


extern char **environ;

extern int (*builtins_func[]) (char **);

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/* print functions */
int _putchar(char str);
void _print(char *str);
void printnum(int n);
void errormsg(char *filename, char *args, int count);

/* string functions */
int _strlen(char *str);
char *_strcat(char *str);
int _strcmp(char *str, char *strcmp);
int _strncmp(char *s1, char *s2, size_t n);

/* execute function */
int execute(char *filename, char **args, int count);

/* builtin functions */
int  env_func(char **args);
int cd_func(char **args);
int exit_func(char **args);
int help_func(char **args);
#endif
