#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <dirent.h>
/*my macros*/
#define INTERACTIVE 1
#define NON_INTERACTIVE_FILE 0
#define NON_INTERACTIVE_PIPED 2
#define ERROR -1
/*Error status macros*/
#define NOT_FOUND 127
#define PERMISSION_DENIED 126
#define EXIT_ERROR 2
#define TOK_D " \t\r\n\a\""
extern char **environ;
/**
 * struct list_path - singly linked list
 * @path: string
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_path
{
	char *path;
	unsigned int len;
	struct list_path *next;
} list_path;
int _strcmp(char *s1, char *s2);
char *_getenv(char *name);
void free_list(list_path *head);
int _strlen(char *s);
ssize_t _getlineHelper(char **lineptr, size_t *n,
		__attribute__((unused)) FILE * stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
list_path *add_node(list_path **head, char *path);
list_path *set_all_paths_to_list();
list_path *set_all_vector_to_list();
char **get_av_with_flags(char *line, int status);
unsigned int char_count(char *str, char c);
/*==========================================================================*/
void free_all(char **lines, int counter, list_path *env,
				list_path *current, char *line, char **line_vector);
int _varcmp(char *var_name, char *full_var);
void _setenv(char *name, char *value, list_path *env_list);
list_path *get_variable(char *name, list_path *head);
size_t print_list(const list_path *p);
void set_list_env(list_path *p);
size_t env_list_len(const list_path *p);
int _cd(char *line_vector[], char **argv);
unsigned int _chrCheck(char c, const char *str);
char *_strtok(char *str, const char *delim);
unsigned int char_count_piped(char *str, char c);
void print_cant_open(char *program_name, int counter, char *file_name);
void is_not_built_in(char **line_vector, char *env[], int *status,
						int counter, list_path *current, char *argv[]);
char **text_to_vector(char *text);
char **file_non_interactive(char *file_name, char *program_name);
char **piped_non_interactive();
char **get_commands(int mode, char *file_name, char *program_name);
void free_l_v(char *line, char **line_vector);
int is_dir(char *line, char **argv, int counter,
			char **line_vector, int *status, char *old_line);
int _atoi(char *s);
void is_exit(char *line, char **line_vector, list_path *current,
		char *program_name, int counter, int *status, list_path *env, char **lines);
void print_error(char *program_name, int counter,
		char *command, int type_of_error);
void handle_comments(char *input);
/*==*/
void handle_semicolons(char *line);
void execute_command_with_waitpid(char *path, char **av, char **env);
/*====*/
char *num_to_char(int num);
char *check_access(char *line_av_1, list_path *current);
void execute_command(char *path, char **av, char **env, int *status);
void print_env(int *status);
char *get_process_id();
char *get_status(int n);
int is_built_in(char *line, char **line_vector, list_path *current,
		char *program_name,
		int counter, int *status, list_path *env, char **lines, char **argv);
void print_error(char *program_name, int counter,
		char *command, int type_of_error);
char *get_command_from_file(char *file);
char *get_command_from_user(list_path *current);
int check_mode(int argc);
void free_vector(char **v);
#endif

