#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shell_loop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_processor.c */
int exec_cmd(info_t *, char *);
char *_charsdup(char *, int, int);
char *_pathlook(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_err.c */
void e_puts(char *);
int e_putchar(char);
int put_fd(char a, int fd);
int puts_fd(char *str, int fd);

/* toem_flow.c */
int str_len(char *);
int cmp_str(char *, char *);
char *startsWith(const char *, const char *);
char *catStr(char *, char *);

/* toem_flow1.c */
char *copy_str(char *, char *);
char *dup_str(const char *);
void _puts(char *);
int _putchar(char);

/* toem_sign_out.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_modifier.c */
char **split_str(char *, char *);
char **split_str2(char *, char);

/* toem_realloca.c */
char *store_set(char *, char, unsigned int);
void free_s(char **);
void *_realloca(void *, unsigned int, unsigned int);

/* toem_store.c */
int free_b(void **);

/* toem_converter.c */
int _interact(info_t *);
int its_delimeter(char, char *);
int its_alphabs(int);
int _converter(char *);

/* toem_err1.c */
int err_converter(char *);
void errorPrinter(info_t *, char *);
int dPrinter(int, int);
char *numberConverter(long int, int, int);
void commentsOmitter(char *);

/* toem_struct.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_struct1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_selectLine.c */
ssize_t select_input(info_t *);
int _selectLine(info_t *, char **, size_t *);
void _handlesigint(int);

/* toem_selectData.c */
void format_info(info_t *);
void arrange_info(info_t *, char **);
void freeInfo(info_t *, int);

/* toem_en_vi.c */
char *selectEnv(info_t *, const char *);
int myEnv(info_t *);
int myset_env(info_t *);
int myunset_env(info_t *);
int popenvList(info_t *);

/* toem_selectEnv.c */
char **select_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* toem_pastRecord.c */
char *collect_record(info_t *info);
int write_record(info_t *info);
int read_record(info_t *info);
int create_record_list(info_t *info, char *buf, int linecount);
int record_renumber(info_t *info);

/* toem_enum_erate.c */
list_t *increase_node(list_t **, const char *, int);
list_t *increase_node_end(list_t **, const char *, int);
size_t list_str_printer(const list_t *);
int delete_indexNode(list_t **, unsigned int);
void freeList(list_t **);

/* toem_enum_erate1.c */
size_t listLen(const list_t *);
char **stringsList(list_t *);
size_t listPrinter(const list_t *);
list_t *startsNode_with(list_t *, char *, char);
ssize_t select_nodeIndex(list_t *, list_t *);

/* toem_variants.c */
int chainTest(info_t *, char *, size_t *);
void chaincheck(info_t *, char *, size_t *, size_t, size_t);
int change_alias(info_t *);
int change_variants(info_t *);
int replace_string(char **, char *);

#endif
