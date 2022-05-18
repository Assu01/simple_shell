#ifndef MAIN_H
#define MAIN_H

extern  char **environ;
/*
* required libraries to be included
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
/**
 * struct filepath - filepath structure
 *
 * @path: path to file
 * @next: pointer to next file
 *
*/
typedef struct filepath
{
	char *path;
	struct filepath *next;
} filep;
char *_readFromFile(char *file);
void exec_file_non_interactive(char **ar);

/*
 * printf function
 */
int _putchar(char p);
int print_n(const va_list ls);
int _printf(const char *format, ...);
int print_char(const va_list a);
int print_string(const va_list b);
int print_modulo(const va_list list);
int num_digits(int n);
void print_num(int n);
int print_b(const va_list);
int len(const char *s);

/*
*temporary
*/
int echo(char **argv, int *exit_status, size_t *count);

int call_setenv(char **argv, int *exit_status,
	int *env_last_state, int *index, int *cur_state,
	int *cur_index, int *add_case, size_t *count);

void execute(char *ar, char *cmd, int *status, int *exit_status,
	int *env_last_state, int *cur_state, int *cur_index,
	int *add_case, int *index, size_t *count);
void execute_non(char *ar, char *cmd, int *status, int *exit_status,
	int *env_last_state, int *cur_state, int *cur_index,
	int *add_case, int *index, size_t *count);
int call_env(int *exit_status, size_t *count);
int call_getenv(char **argv, int *exit_status, size_t *count);
int cd_prev(int *exit_status, int *env_last_state, int *index,
	int *cur_state, int *cur_index, int *add_case, size_t *count, char *ar);
int cd_home(int *exit_status, int *env_last_state, int *index,
	int *cur_state, int *cur_index, int *add_case, size_t *count, char *ar);
void free_environ_exit(int *env_last_state, int *index, int *add_case);
void free_environ(char **old_env, int *env_last_state,
	int *index, int cur_state, int cur_index);
int init_exec(size_t, char *, char **argv, int *exit_status,
	int *env_last_state, int *index, int *, int *, int *, size_t *, char *);
int exec_builtin(char **argv, int *exit_status,
	int *env_last_state, int *index, int *, int *, int *, size_t *, char *);
int cd(char **argv, int *exit_status, int *env_last_state,
	int *index, int *, int *, int *, size_t *, char *);
char *get_absolute_path(char *name);
/*
*malloc free functions
*/
void free_all(char **argv, char *p_cwd, char *p_path, char *p_abs);

/*
* maths operations
*/
size_t _power(size_t, size_t);
size_t _atoi(char *);
/*
*utility 2
*/
void exec_parent(char *, int *, char *, char **, int *);
void free_ptr(char *ptr);
void free_dblptr(char **argv, char *cmd);
int check_empty_space(char *s);
void __exit(char **, char *, char **, int *, int *, int *);
void __exit_semi(char **, char **, char *, char **, int *, int *, int *);
/*
* path functions
*/
char *_getcwd();
char *check_in_cwd(char *filename);
char *check_in_path(char *filename);
char *get_full_path(char *filename, char *homedir);
char *get_path_in_cwd(char *filename);
/*
* linked list functions
*/

filep *gethead();
void free_list(filep *head);
int set_next(char *p, size_t i, filep  *current);
/*
* string functions
*/
size_t _strlen(const char *s);
char *_strtok(char *s, char **p, char *sep);
int _strcmp(char *src, char *dest);
int _strcpy(char *src, char *dest);
size_t len_words(char **s);
int _memset(char *mem, size_t size);
size_t len_from_to(char *p, int start, char stop);
int _strcmp_index(char *src, char *dest);
void _strcpy_index(char *src, char *dest, size_t start_index);
/*
* environmental var functions
*/

int  _setenv(const char *name, const char *value, int overwrite,
	int *, int *, int *, int *, int *);
int _unsetenv(const char *name);
int  _addenv(const char *name, const char *value, int *,
	int *, int *, int *, int *);
char *_getenv(const char *name);
int  _getindex(const char *name);
char *getenv_index(char *name);
int free_null_env(char **newenv, ssize_t i);
void print_env(char **env);
/*
* getline functions
*/

char *_readline();
char *_interline();
/*
* built in functions
*/
char *get_abs_path(char **argv, char *path_cwd, char *path_in_path);
int is_builtin(char *argv1, char *argv2);
void exec_non_interactive(char **ar);
#endif
