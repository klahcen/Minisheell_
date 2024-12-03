/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:03:09 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/04 17:22:34 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
// # include <readline/history.h>
// # include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// #define BUFFER_SIZE 1024
# define SPECIAL_CHAR '#'
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define READLINE_LIBRARY
# include "/Users/lkazaz/readline/include/readline/history.h"
# include "/Users/lkazaz/readline/include/readline/readline.h"

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_node
{
	char				*args;
	struct s_node		*next;
}						t_node;

typedef struct s_redirect
{
	char				*file;
	char				*lim;
	int					status;
	t_env				*envir;
	int					fd;
	int					pip[2];
	int					type;
	struct s_redirect	*next;
}						t_redirect;

/*
1 s_redirect output >
2 s_redirect input <
3 s_redirect output append >>
4 s_redirect here document <<
*/

typedef struct s_pipe
{
	char				*cmd;
	int					index;
	char				*string;
	struct s_pipe		*next;
}						t_pipe;

typedef struct s_redirin
{
	char				*file;
	int					fd;
	struct s_redirin	*next;
}						t_redirin;

typedef struct s_cmd
{
	char				**args;
	char				*cmd;
	int					**fd;
	int					num_pip;
	char				*flags;
	char				*files;
	t_redirin			*redirin;
	t_redirect			*redirect;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_list
{
	void				*ptr;
	struct s_list		*next;
}						t_list;

typedef struct s_all
{
	t_list				*g_alloc;
	int					status;
	int					nbr_herdoc;
	int					c;
	int					q;
}						t_all;

t_all			g_all;

typedef struct s_mini
{
	t_redirect			*redirect;
	t_redirect			*first_redirect;
	t_redirect			*current_redirect;
	t_redirect			*new_redirect;
	t_cmd				*cmd;
	t_cmd				*current_cmd;
	t_cmd				*cmd_path;
	t_cmd				*new_cmd;
	t_node				*tmp1;
	char				**args;
	char				*strtrim;
	int					expanded;
	int					i;
	int					j;
	int					flag;
}						t_mini;

typedef struct s_parse
{
	t_node				*node;
	t_node				*tmp;
	char				*str;
	char				**pipe;
	int					i;
	int					j;
}						t_parse;

typedef struct s_exe
{
	t_cmd				*tmp;
	t_cmd				*cmd1;
	t_cmd				*cmd2;
	char				**env;
	char				*s1;
	char				*s2;
	char				*s3;
	int					**f;
	int					*pid;
	int					pip;
	int					len;
	int					status;
	int					i;
	int					j;
	int					k;
	int					ac;
	int					fd;
}						t_exe;

typedef struct s_exea
{
	t_exe				exe;
	t_cmd				*tmp;
	t_cmd				*tmp1;
	int					nbr_her;
	t_cmd				*temp;
	int					pid;
}						t_exea;

typedef struct s_exea1
{
	t_env				*last;
	char				**str;
	char				*src;
	int					index;

}						t_norrr;

void					ft_norm_next(t_cmd *cmd, t_env **envir, t_exea nor);
void					ft_exit_her_doc(t_exea nor);
int						ft_nbr_her(t_cmd *tmp);
int						ft_buil(t_cmd *cmd, t_env **envir, int pip);
void					ft_next_echo(t_cmd *tmp, char *str, int i);
int						ft_red_next(t_redirect *red);
void					ft_next_echo(t_cmd *tmp, char *str, int i);

// ft_split.c
char					**ft_split(char const *s, char c);

// ft_utils.c
int						ft_strcmp(char *s1, char *s2);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
t_env					*ft_create_env(char *name, char *value);
void					*ft_malloc(size_t size);
void					ft_free_all(t_env *envir);

// ft_store.c
t_env					*ft_get_env(char **env);

char					*ft_set_spaces(char *input);
void					ft_putstr_fd(char *s, int fd);

// exc
void					ft_execute(t_cmd *cmd, t_env **envir);
void					ft_exec(t_cmd *tmp, char **env, t_env **envir,
							t_cmd *cmd1);
void					new_pipe(t_cmd *data);
void					ft_close(t_cmd *data, int i);
char					*ft_strstr(char *str, char *to_find);
int						ft_strrch(char *str, char c);
char					*ft_substrr(char *str, int i);
char					**ft_next_env(t_env *envir, char **env);
t_redirect				*ft_lstl(t_redirect *lst);
char					*ft_advance_expand(char *str, t_env *envir);
void					ft_next_red(t_redirect *red);
void					ft_redirect(t_redirect *red);
void					ft_error(char *str);
void					ft_closered(t_cmd *data);
void					ft_closered1(t_cmd *data);

// built
char					**ft_env(t_env *envir);
int						ft_echo(t_cmd *tmp);
int						ft_pwd(void);
int						ft_cd(t_cmd *tmp, t_env *envir);
int						ft_builtins(t_cmd *tmp, t_env **envir);
char					*t_getdata(t_env *envir, char *str);
void					ft_modifenv(t_env *envir, char *chr, char *new);
t_env					*ft_lstlast(t_env *lst);
int						ft_isalpha(int a);
int						ft_exit(t_cmd *cmd);
void					ft_lstadd_back(t_env **lst, t_env *new);
int						ft_affichenv(t_env *envir);
int						ft_isdigit(int c);
void					ft_sorte(char **str);
int						ft_next_unset(char **str, t_env *temp, int i,
							t_env **head_ref);

// sysntax
int						ft_syntax_error(char *str);
void					ft_execred(t_cmd *tmp, t_env *envir);

// ft_quotes.c
char					*remove_all_quotes(char *str);
char					*ft_calloc(size_t count, size_t size);
void					ft_red_doc(t_redirect *tmp);
t_redirect				*ft_lstl(t_redirect *lst);

// ft_utils1.c
int						ft_isalnum(char c);
int						is_quote(char c);
char					*ft_join(char *str1, char *str2);
t_cmd					*ft_error1(char *str);

// ft_utils2.c
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strchr(const char *s, int c);
int						ft_strlcpy(char *dst, const char *src, int size);
int						ft_strlen(char *str);
int						ft_args_len(char **args);

// ft_utils3.c
char					*ft_strdup(char *str);
char					*ft_substr(char *s, int start, int len);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strjoin2(char *s1, char *s2, char *s3);
char					*ft_strtrim(char *str, char *set);

// ft_split2.c
char					**ft_split2(char *str, char *s);
char					*ft_last_world(char *str);

// ft_expand.c
char					*ft_remove_dollar(char *str);
int						can_expand(char *str);
char					*ft_expand(char *str, t_env *envir, int *expanded);
char					**ft_process_args(char **args, t_env **envir);

// ft_help_expand.c
int						str_isnt_in_env(char *str, t_env *envir);

// ft_set_args.c
t_cmd					*ft_set_arguments(char **args, t_cmd *cmd,
							t_redirect *first_redirect);
t_cmd					*ft_set_arguments2(char **args, t_cmd *cmd, int i,
							int j);
void					ft_norm_hna(char **args, int *fd, int *i,
							t_redirect *first_redirect);

// ft_minishell.c
void					ft_minishell(t_node *node, t_env **envir);
t_cmd					*ft_process_commands(t_mini *mini, t_env **envir);
void					ft_process_redirect(t_mini *mini, t_env **envir);

// ft_parsing.c
void					ft_parse_input(char *input, t_env **envir);
int						string_is_spaces(char *str);
void					ft_check_pipe(char **pipe);
void					ft_ascii(void);

// ft_redirection.c
t_redirect				*ft_redirection(char **args);

// ft_path.c
t_cmd					*ft_get_path(t_cmd *cmd, t_env *envir);
char					*ft_get_env_value(char *name, t_env *envir);

// ft_expand1.c
char					*ft_itoa(int n);
char					*ft_expand_hadi(char *str);

int						ft_strrch(char *str, char c);
char					*ft_substrr(char *str, int i);

void					handle(int signum);
void					handle2(int signum);
int						ft_atoi(char *str);
int						gha_error(char *str);

#endif