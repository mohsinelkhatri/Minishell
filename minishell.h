/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:43:28 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 13:00:17 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MAX_LINE 1024

typedef enum s_token_type
{
	T_WORD,
	T_PIPE,
	T_DGREAT,
	T_GREAT,
	T_HEREDOC,
	T_LESS,
}							t_token_type;

typedef struct s_redriction
{
	t_token_type			type;
	char					*file;
	struct s_redriction		*next;
}							t_redir;

typedef struct s_spcmd
{
	char					**cmd;
	t_redir					*redir;
	struct s_spcmd			*next;

}							t_spcmd;

typedef struct s_qout
{
	int						i;
	int						in_quote;
	char					quote_char;
	char					*result;
	char					*tmp;
}							t_qout;

typedef struct s_cmd
{
	char					*cmd;
	char					*token;

}							t_cmd;

typedef struct s_dolar
{
	int						i;
	char					*result;
	char					*tmp;
	char					*var_name;
	char					*var_value;
	int						in_single_quote;
	int						in_double_quote;
	int						start;
	int						retu;
}							t_dolar;

typedef struct s_list
{
	char					*content;
	int						remove_qoute;
	t_token_type			type;
	struct s_list			*next;
}							t_list;

typedef struct s_sqout
{
	int						i;
	int						in_quote;
	char					quote_char;
	int						in_double_quote;
	char					*result;
	char					*tmp;
	char					*new_res;
}							t_sqout;

typedef struct s_dolar2
{
	t_list					*tmp;
	t_list					*current;
	t_list					*processed;
}							t_dolar2;

typedef struct s_processnode
{
	int						i;
	int						start;
	int						sp;
	char					*result;
	char					*helper;
	char					*first;
	char					*env_name;
	char					*env_val;
	t_list					*tmp;
}							t_pd;

typedef struct s_sig
{
	int						sigint;
	int						sigquit;
	int						exit_status;
	pid_t					pid;
}							t_sig;

typedef struct s_lst_garbage
{
	void					*ptr;
	struct s_lst_garbage	*next;
}							t_lst_garbage;

typedef struct data
{
	t_lst_garbage			*lst_gc_g;
	t_lst_garbage			*lst_gc_env;
}							t_data;

typedef struct s_split
{
	int						i;
	int						start;
	t_list					*head;
}							t_split;

typedef struct s_env
{
	char					*var;
	char					*val;
	struct s_env			*next;
}							t_env;

void						paring_cmd(char *cmd, t_env **env);
t_data						*set_get_data(void *p);
void						free_garbage(t_lst_garbage **head);
t_list						*split_cmd(char *str, int flag);
char						**reverse_env(t_env *lst);
void						*ft_malloc(size_t size, t_lst_garbage **head);
t_list						*fill_node(char *content, t_token_type t_type,
								int rm_qu);
int							ft_lstadd_back(t_list **lst, t_list *new);
int							checking_close_qoutes(char *str);
int							is_meta(char str);
int							checking_cmd(t_list **list, t_env **env);
void						update_env(const char *key, const char *value,
								t_env *env);
t_list						*convert_dolar2(t_list **list, t_env *env);
char						*checking_dolar(char *str, t_env *env);
char						*skip_qouts(char *str, int rm_qu);
t_data						*set_get_data(void *p);
pid_t						fork_and_execute(t_spcmd *curr, int fd_in,
								int pipefd[2], t_env *env);
t_spcmd						*parse_command_segment(t_list **tmp_ptr);
void						spcmd_lstadd_back(t_spcmd **lst, t_spcmd *new_node);
int							handle_word_token(char *str, int *i, t_list **head,
								int flag);
void						parc_token(t_list *list, t_env **env);
int							handle_meta_token(char *str, int *i, t_list **head);
void						child_process(t_spcmd *curr, int fd_in,
								int pipefd[2], t_env *env);
void						init_st(t_dolar2 *st, t_list *list);
void						handle_fork_error(void);
int							validate_cd_args(t_spcmd *lst, t_env **env);
void						cleanup_heredoc_files(t_list *hd);
void						sigint_handler(int signum);
int							change_directory(char *path, t_env **env);
void						update_oldpwd(char *old_path, t_env **env);
int							handle_getcwd_error(char *old_path, t_env **env);
t_env						*init_shell(char **env, t_data *data);
char						*extract_quoted_substring(char *str, int *index,
								char quote_char);
void						skip_whitespace(char *str, int *i);
int							check_sudo(const char *cmd);
void						handle_dollar_quote(char *str, t_pd *pd);
void						print_command_error(const char *cmd,
								char *path_env);
void						setup_signals(void);
int							process_command_line(t_env **lst, t_data *data);
t_list						*process_node_content2(char *str, t_env *lst,
								int flag);
void						init_parc(t_spcmd **cmd, int *i, int size);
int							skip_spaces(char *str, int i);
void						setup_child_io(t_spcmd *curr, int fd_in,
								int pipefd[2]);
t_redir						*new_redir(t_token_type type, const char *file);
void						execute_command(t_spcmd *curr, t_env *env);
void						print_error_message(const char *cmd,
								const char *message);
int							get_last_node_content(t_list *head);
int							check_space(char *str);
int							count_spcmd_nodes(t_spcmd *head);
int							present_dolar(char *str);
void						redir_lstadd_back(t_redir **lst, t_redir *new);
int							is_redirection(t_token_type type);
void						print_error_message(const char *cmd,
								const char *message);
void						parc_token(t_list *list, t_env **env);
void						ft_exuction(t_spcmd *list, t_env **env);
void						print_env(t_env *env);
void						ft_unset(t_spcmd *lst, t_env **env);
void						ft_cd(t_spcmd *lst, t_env **env);
int							check_env(char *var, char *val, t_env *lst);
void						ft_exit(char **cmd, t_env *env);
int							check_nber(char *str);
int							get_last_node_content(t_list *head);
char						*ft_getenv(char *str, t_env *lst);

t_env						*copy_env(char **str);
char						*ft_strdup_env(const char *s);
t_env						*ft_env_new(char *var, char *val);
void						ft_env_add_back(t_env **head, t_env *new_node);
void						ft_export(char *str, t_env **env);
void						ft_export_hp(t_spcmd *lst, t_env **env);
void						srch(char *str, int *i);
int							ft_strcmp(const char *s1, const char *s2);
char						*heredoc(char *delimiter);
void						handle_redirections(t_redir *redir);
t_env						*set_get_env(t_env *p);
void						update_exit_status(t_env *env, int status);
int							is_built_in(char *str);
void						handle_dolar(t_dolar *dolar, char *str, t_env *env);
void						init_dolar(t_dolar *dolar);
int							is_numeric(const char *str);
int							check_nber(char *str);
void						ex_echo(t_spcmd *lst, t_env *env);
void						printf_pwd(t_env *env);
void						update_env(const char *key, const char *value,
								t_env *env);
void						ft_exit(char **cmd, t_env *env);
void						parc_token(t_list *list, t_env **env);
int							ex_built_in(t_spcmd *lst, t_env **env);
int							env_len(t_env *env);
char						*str_join_var_val(t_env *env);
char						**env_to_array(t_env *env);
char						*ft_strjoin3(const char *s1, const char *s2,
								const char *s3);
char						*get_cmd_path(char *cmd, t_env *env);
void						execute_external(t_spcmd *lst, t_env *env);
void						ft_export(char *str, t_env **env);
char						*join_tokens_with_spaces(t_list *tokens);
int							is_valid_var_name(char *str);
int							is_directory(const char *path);
char						*get_env_value(const char *key, t_env *env);
void						ft_cd(t_spcmd *lst, t_env **env);
void						srch(char *str, int *i);
t_list						*split_dolar(char *str);
int							create_pipe_if_needed(t_spcmd *curr, int pipefd[2]);
void						close_fds_parent(int *fd_in, int pipefd[2],
								t_spcmd *curr);
void						wait_for_children(pid_t *pids, int cmd_count);
void						handle_exec_error(char *cmd_name);
void						setup_fd(int fd_in, int pipefd[2], t_spcmd *cmd);
void						join_lists(t_list **a, t_list *b);
void						handle_assignment(char *str, t_pd *pd);
void						handle_env_variable(char *str, t_pd *pd,
								t_env *lst);
char						*join_in_dqout(char *str);
void						handle_env_with_spaces(t_pd *pd);
t_list						*chr_meta(char *str, int *i);
void						init_pd(t_pd *pd);
void						execute_pipeline(t_spcmd *list, t_env *env);
void						get_pos(char *str, int *i);
int							in_qout(char *str);
void						handle_quoted_string(char *str, t_pd *pd);
void						handle_child_process(t_spcmd *lst, t_env *env,
								char *path_env);
int							is_delimiter(const char *line,
								const char *delimiter);
char						*heredoc(char *str);
char						*get_without_trailing_slash(const char *str);
void						handle_sudo_case(const char *cmd, char *cmd_path);
char						*open_rd_file(void);
void						paring_cmd(char *cmd, t_env **env);
int							is_slash(const char *path);
t_list						*split_cmd(char *str, int flag);
char						*read_line_or_delimiter(char *delimiter);
int							handle_getcwd_errorrr(char *path_old, t_env **env);
void						update_pwd(char *path_nw, t_env **env);
int							handle_single_token(t_list *tmp, t_list *hd,
								t_env *env, int *flag);
int							process_token_list(t_list *hd, t_env *env);
void						handle_sigint_heredoc(int sig);
int							process_heredoc_token(t_list *tmp, t_list *hd);
char						*checking_dolar_doc(char *str, t_env *env);
void						find_and_remove_var(char *var_name, t_env **env);
#endif