/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:35:44 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/30 16:01:37 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./defines.h"
# include "./libft.h"
# include "./structs.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_minishell
{
	char	**env;
	char	*pwd;
	char	*oldpwd;
	t_list	*history;
	char	*history_path;
	int		exit_status;
	t_node	*root;
	t_bool	is_parent;
	t_bool	is_oldpwd_unset;
}			t_minishell;

/* REDIRECTS */
int			apply_redirects(char **redirs, t_minishell *minish);
int			check_redir(char **redir, t_minishell *minish);
int			apply_heredoc(char *limiter, int *in);
int			apply_redir_in(char *str, t_minishell *minish, int *in);
int			apply_append(char *redir, t_minishell *minish, int *out);
int			apply_redir_out(char *redir, t_minishell *minish, int *out);
int			prepare_redirects(char *redirects_line, int *hd_num, char ***redirs,
				t_minishell *minish);
int			prepare_heredoc(char **limiter, char *hd_name, t_minishell *minish);
void		remove_hd_dups(char ***redirs, char *hd_name, char hd_counter);

/* TREE TRAVERSAL */
int			find_cmd(char **cmd, char **penv);
int			find_exe(char **cmnd, char **paths);
int			is_builtin(char *cmd);
int			parse_cmd(char *cmd, char ***res, t_minishell *minish);

/* UTILS */
void		remove_quotes(char *str, int i, int j);
void		remove_quotes_arr(char **arr, int i);
void		syntax_err_msg(char *str);
void		print_err_msg(char *cmd, char *msg);
void		perror_err_msg(char *cmd, char *arg);
void		arg_err_msg(char *cmd, char *arg, char *msg);
void		handle_ctl_d_error(char *msg);
int			handle_ctl_d(char *prompt);
char		**wrapper_split_quotes(char *str);

/* VALIDATE SYNTAX */
char		*validate_redirect(char *str, t_bool *status);
char		*validate_word(char *str, t_bool *status);
t_bool		string_is_empty(char *str);

#endif
