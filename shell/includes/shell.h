/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 12:04:27 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/17 14:20:12 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "libft.h"
# include "line_edition.h"
# include "parsin.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <assert.h>

/*
** metacharacters
*/
# define BACKSLACH '\\'
# define SQUOTE '\''
# define DQUOTE '"'
# define HASH '#'
# define PIPE '|'

/*
** DATASTRUCTURES;
*/

typedef struct s_env	t_env;
typedef struct s__mc	t__mc;
typedef	struct s_var	t_var;
typedef	struct s_info	t_info;
typedef	struct s_cmd	t_cmd;
typedef	struct s_index	t_index;
typedef	struct s_quote	t_quote;
typedef	struct s_holder	t_holder;
typedef	struct s_childs	t_childs;

/*
** ENVIRONEMENT;
*/
struct		s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
};

/*
** PRE_PARSE LIST;
*/
struct		s__mc
{
	char			**cmd;
	struct s__mc	*next;
};

/*
** QUOTE HANDLER IN RECALL READLINE;
*/
struct		s_var
{
	int		a;
	int		b;
	int		c;
	int		d;
	int		index;
};

/*
** MAIN LIST;
*/
struct		s_info
{
	char			*file;
	int				sfd;
	int				dfd;
	int				read_meth;
	struct s_info	*next;
};

struct		s_cmd
{
	char			**cmd;
	struct s_info	*red;
	struct s_cmd	*next;
};

/*
** QUOTING STRUCT FOR PARSIN;
*/
struct		s_index
{
	int		i;
	int		j;
	int		v;
};

struct		s_quote
{
	int		keeper;
	int		definer;
	t_env	*env;
};

/*
** DATA STRUCTURE HOLDER;
*/
struct		s_holder
{
	t_env	*head_ref;
	t__mc	*mclst;
	t_cmd	*lst;
	char	*line;
	char	*linecpy;
	int		linecpyflag;
	t_his	*his_tail;
	char	*heredoc;
	char	*ptr;
	char	*stctmp;
	char	*tmp;
	int		hdocflg;
};

/*
** CHILDS_LIST;
*/
struct		s_childs
{
	pid_t			child;
	int				index;
	struct s_childs	*next;
};

/*
** PARSIN;
*/

char		*parsin(char *line, t_env *env);
char		*token_manager(char *str, char *line, int *i);
char		*escape_character(char *str, char *line, int *i, t_quote q_r);
char		*ignore_quote(char *line);
void		add_file(t_cmd **lst, t_info **head, char **cmd, t_index *l);
void		add_casual(t_cmd **lst, t_info **head, char **kratos, t_index *l);
char		*error_assembly(int fd);
t_info		*create_info(char *kratos, char *file, t_index *l, t_index def);
t__mc		*mc_maker(char *line, t_env *env);
t_cmd		*last_splice(t__mc **old_lst, t_env *env);
int			syntax_error(char *line);

/*
** COUNT;
*/

int			count_arg(char **cmd);
int			count_mclst(t__mc *lst);
int			count_lstgod(t_cmd *lst);
int			len_of_list(t_env **head_ref);

/*
** CHECK;
*/

int			ultimate_check(char *kratos);
int			ft_iswhite(char c);
int			got_no_token(char *kratos);
int			is_a_builtin(char *cmd);
int			check_red(t_info *lst);
int			just_spaces(char *line);
int			cmd_is_found(char **tab, char **ptrcmd, char *temp);

/*
** $ FUNCTIONS PARSIN;
*/

char		*dollar_get_simple(char *name, t_env *env, char **ptr);
char		*dollar_get_quoted(char *name, t_env *env, char **ptr);
char		*dollar_handle_simple(char *toto, char *line, int *i, t_env *env);
char		*dollar_handle_quoted(char *toto, char *line, int *i, t_quote sp);

/*
** SHELL FUNCTIONS;
*/

void		shell(t_holder *h);
void		child_pid(char **command, t_cmd *lst, t_env **head_ref, pid_t *get);
void		print_lstra(t_cmd *lst);
int			retrieve_the_digit(char *name, int	delimiter);
void		darlin_g(t_holder *h);
int			deathly_hallows(t_info *lst, t_info **head);
t_childs	*create_child(pid_t child_pid, int *t, int def);
void		kill_pid(t_childs *c_head, int *keeper);
void		cheap_trick(int *keeper, int trick);
void		sys_cmd(char **command, char *path_found, \
			t_env **head_ref, pid_t *get);
void		execute(char **command, char *path_found, \
			t_env **head_ref, pid_t *get);
char		**get_env(t_env **head_ref);
void		builtin_cmds(t_holder *h, int j);
void		builtin_cmds_1(t_holder *h, int j, int i, int flag);
void		which_cmd(char *arg, t_env **head_ref);
int			own_commands(char *ptab);
void		del_node(char *s, t_env **head_ref);
void		add_node(t_env **head_ref, char *s1, int flag);
void		add_node_1(t_env *curr, t_env *new_node);
void		echo_cmd(char *arg, char *narg, int flag);
int			specialchar(char *s);
void		ft_chdir(char *path, char *cwd, t_env **head_ref, int flag);
void		swap(t_env **head_ref, char *lastcwd, char *cwd);
void		reset_fds(void);
char		*get_var(char *deli, t_env **head_ref);
void		print_env(t_env **head_ref);
t_env		*copy_of_env(char **tab);
void		history_terminator(t_holder *h);
void		createlist(t_env **head_ref, t_env **tail, char *var);
char		**get_path(t_env **head_ref);
int			find_path(char *penv);
void		signal_handler(int sign);
int			setenv_cmd(char *arg, char *sarg, t_env **head_ref, int flag);
void		keephistory(t_his **his_tail, char *hline, t_holder *h);
void		keephistorylst(t_his **his_tail, char *hline);

/*
** - Gestion Error;
*/

void		env_gerror(int flag);
int			error_cases(char **arr);
void		chdir_gerror(char *path, int flag);
void		path_gestion_error(char *path);

/*
** readline and recall of readline;
** heredoc and quotes functions;
*/

char		*recall_readline(t_holder *h);
char		*ft_readline(char prompt[3], t_his *his_tail, int his_flag);
int			metacharacters(char ch, int flag);
int			heredoc_handler(t_holder *h, char **line);
int			meta_handler(char *line, int *flag);
int			get_len_before_heredoc(char *str, int counter);
int			get_len_of_needle(char *s);
char		*heredoc_new_line(char **tmp, char **line);

/*
** FREE;
*/

void		free_structure(t_holder *h, int flag);
void		free_list_mc(t__mc *lst);
void		free_list_env(t_env **head_ref);
void		free_main_lst(t_cmd *lst);
void		free_list_history(t_his *his_tail);
void		free_child(t_childs *lst);
void		free_heredoc_helper(char *needle, char *s);

#endif
