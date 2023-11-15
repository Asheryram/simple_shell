#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

/* included standard library headers */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <signal.h>

/* included custom headers */
#include "structs.h"


/* this defines the macros for token_t struct */
#define TO_KEN_STRING     0
#define TO_KEN_SE_MI_CO_LON  1
#define TO_KEN_PIPE       2
#define TO_KEN_RE_WRITE    3
#define TO_KEN_AP_PEND     4
#define TO_KEN_CAT       5
#define TO_KEN_BACK_GROUND 6
#define TO_KEN_AND        7
#define TO_KEN_OR         8



/* ---------------------MACROS---------------- */
#define BU_FFER_SIZE 1024
#define EX_IT_SUC_CESS 0
#define EX_IT_FAI_LURE1
#define TRUE_THY (1 == 1)
#define FALSE_THY (!TRUE_THY)


/* -----environ----- */
extern char **environ;

/* ---------------main--------------- */
ssize_t _get_line(char **buffer, size_t *limit);
int _file_mode(int fd);
ssize_t _read_line(int fd, char **buffer, size_t *limit);

/* --------- arguments inventory ---------- */
arg_in_ven_tory_t *build_arg_inv(void);
char *set_name(env_ment *env_list, char *name);

/* ---------------exe_cute--------------- */
pid_t exe_cute(arg_in_ven_tory_t *arginv);
int exec_builtins(arg_in_ven_tory_t *arginv);
pid_t exec_path(char *command, arg_in_ven_tory_t *arginv);

/* -------custom environ------- */
env_ment *env_list(void);
char **se_pa_rate_string(char *string);
unsigned int link_counts(env_ment *head);
char **link_to_poin_ter(env_ment *head);
env_ment *add_node_env_ment_ment(env_ment **head, char *var, char *val);
int put_node_env_ment_ment(env_ment **head, char *new_var, char *new_val);
int del_node_env_ment_ment(env_ment **head, char *var);


/* ---------------gen_tokenr--------------- */
int del_tokens(tokens_t *tokens);
void gen_token(tokens_t *tokens, const char *string);
int re_di_rec_tion(int token_id);
void init_to_kens(tokens_t *tokens, int length);
void del_dups(tokens_t *tokens);
void token_clasify(tokens_t *tokens);
void clean_to_kens(tokens_t *tokens, unsigned int tokens_idx, char *data);





/* -----custom C std lib----- */
char _is_t_space(char c);
int _a_to_oi(char *s);
void _process_err(char *string);
void _chg_mem_loc(void *dest, void *src, size_t n);
int is_unsgn_int(char *num);

/* ---------------strings--------------- */
char *_strng_co_py(char *dest, char *src, int n);
char *_str_dupp(char *str);
unsigned int _str_length(const char *str);
char *_str_co_py(char *dest, char *src);
char *_strn_cat(char *dest, char *src, int n);
int _strg_com_pare(const char *s1, const char *s2);
int _strng_com_pare(char *s1, char *s2, unsigned int n);
int _un_set_env(arg_in_ven_tory_t *arginv);
char *_str_categ(char *dest, char *src);
char *int_t_to_str_t(unsigned int n);
void repl_str_all(char **old_str, char *new_str, int i, int j, int flg);
char *_str_repl(char *string, unsigned int start, unsigned int end,
				   char *rep);

/* ---------------builtin--------------- */
int _env_ment(arg_in_ven_tory_t *arginv);
int _set_env_ment(arg_in_ven_tory_t *arginv);
int _past_time(arg_in_ven_tory_t *arginv);
int _cee_dee(arg_in_ven_tory_t *arginv);
int _al_ias(arg_in_ven_tory_t *arginv);
int _un_al_ias(arg_in_ven_tory_t *arginv);
int she_ll_helper(arg_in_ven_tory_t *arginv);
int up_load_al_ias(arg_in_ven_tory_t *arginv);
int perm_ali_as(arg_in_ven_tory_t *arginv);
int she_ll_close(arg_in_ven_tory_t *arginv);




/* ---------------custom malloc---- @senyodey----------- */
char *mem_reset(char *str, int bytes);
void *safe_malloc(int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* ---------------history--------------- */
history_t *history_list(arg_in_ven_tory_t *arginv);
history_t *add_node_history(history_t **head, char *command);
int file_history(arg_in_ven_tory_t *arginv);
char *history_to_string(history_t *head);
history_t *init_history(history_t *head, char *buffer);

/* -----alias----- */
int write_alias(alias_t *head);
alias_t *alias_list(void);
alias_t *add_node_alias(alias_t **head, char *alias, char *command);
int modify_node_alias(alias_t **head, char *new_var, char *new_val);
int remove_node_alias(alias_t **head, char *var);
alias_t *fetch_node_alias(alias_t *head, char *var);

/* ---------------cd--------------- */
char *file_path(char **commands, env_ment *env_list);
env_ment *fetch_node(env_ment *head, char *var);

/* ---------------printer--------------- */
int write_uint(unsigned int n);
unsigned int write_history(history_t *head);
void _puts(char *str);
size_t print_list(env_ment *head);
int _putchar(char c);

/* ---------------file I/O--------------- */
ssize_t read_textfile(char *filename, size_t letters);
int trunc_text_to_file(char *filename, char *text_content);
int append_text_to_file(char *filename, char *text_content);

/* ---------------link_path--------------- */
int locate_path(char *path, env_ment *env_list);
int cat_path(char **search_path, char *cmd);
int is_path(char *command);
int count_paths(char *path_str);
char **gen_token_path(char *path_str);
void free_paths(char **paths);

/* ---------------parsetree--------------- */
ptree_t *ptree_new_node(ptree_t *parent);
ptree_t *ptree_new_string_node(ptree_t *parent, tokens_t *tokens,
							   unsigned int *cur_token);
int delete_ptree(ptree_t *node);

/* ---------------parser--------------- */
int parse_error(token_t *near);
ptree_t *parse_expr(unsigned int *ntoken, tokens_t *tokens, ptree_t *lhs,
					int min_prec);
int parse(parser_t *parser, tokens_t *tokens);
int delete_parser(parser_t *parser);
void expand_bash_vars(arg_in_ven_tory_t *arginv);
int expand_alias(arg_in_ven_tory_t *arginv);

/* ---------------processor--------------- */
unsigned int init_pipeline_count_processes(ptree_t *tree);
int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree);
int init_pipeline(pipeline_t *pipeline, ptree_t *ptree);
int process_exe_cute_core(arg_in_ven_tory_t *arginv);
int process_exe_cute(arg_in_ven_tory_t *arginv);
int delete_pipeline(pipeline_t *pipeline);

/* ---------------free--------------- */
int freeall(arg_in_ven_tory_t *arginv);
int free_env_mentiron(env_ment *head);
int free_history(history_t *head);
int free_alias(alias_t *head);

/* ----help---- */
void help_exit(void);
void help_env_ment(void);
void help_set_env_ment(void);
void help_unsetenv(void);
void help_history(void);
void help_cd(void);
void help_alias(void);
void help_help(void);

#endif
