#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

extern int exitcode;
extern int errorcount;

/* check_helpers */
int exit_check(char *user_input, char *NAME);
int blank_check(char *user_input);
int path_check(char *command);
int env_check(char *user_input);

/* error_helpers */
void command_error(char *NAME, char *command);
void exec_error(char *NAME, char *command);
void access_error(char *NAME, char *command);
void exit_error(char *NAME, char *user_input);

/* fork_wait_exec */
void fork_wait_exec(char **commands, char **path_array,
		    char **env, char *NAME, char *user_input);

/* memory_helpers */
void free_array(char **array);

/* number_helpers */
int _atoi(char *s);
void print_number(int n);

/* parse_input */
int arg_counter(char *user_input);
char **parse_input(char *user_input, char **path_array, char *NAME);

/* string_helpers */
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
int _putchar(char c);

/* env_helpers */
int get_path_count(char *path);
char **get_path_array(char **env);
char *find_path(char **path_array, char *token);
void print_env(char **env);

/* splash screen */
void display_splash_screen(FILE *file_ptr);

#endif
