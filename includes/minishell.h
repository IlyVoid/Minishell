/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:35:44 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 18:22:05 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./defines.h"
# include "./libft.h"
# include "./structs.h"

typedef struct s_minishell
{
	char	**env;
	char	*pwd;
	char	*oldpwd;
	t_list	*history;
	char	*history_path;
	int		exit_status;
	t_node	*root;
	bool	is_parent;
	bool	is_oldpwd_unset;
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
int			bracket_traverser(t_node **node, t_minishell *minish);
int			builtin_runner(char **cmd, char **redir, t_minishell *minish,
				int cmd_type);
int			cmd_traverser(char *cmd, char **redir, t_minishell *minish);
int			cmd_br_traverser(t_node **root, t_minishell *minish);
int			pipe_traverser(t_node **root, t_minishell *minish);
int			tree_traverser(t_node **root, t_minishell *minish);
int			and_traverser(t_node **root, t_minishell *minish);
int			or_traverser(t_node **root, t_minishell *minish);
int			wait_childs(pid_t *pids, int num);

/* EXECUTOR */
void		run_cd(char **arr, t_minishell *minish, int status);
int			cmd_run(char **arr, t_minishell *minish, int cmd_type);
void		run_echo(char **arr, int i, int j, int nl_flag);
void		run_pwd(char **arr, t_minishell *minish);
void		run_env(char **arr, t_minishell *minish);
void		run_exit(char **arr, t_minishell *minish, long nbr);
void		run_unset(char **arr, t_minishell *minish);
void		skip_char(char *str, int *i, int symb);
void		end_process(t_minishell *minish);
void		exec_unset(char ***penv, int pos, int i);
int			env_var(char **penv, char *var, int i, int j);
t_bool		ft_isenv(char c, int *j);
int			arg_var(char **arr, char *var, int i, int j);
void		struct_update_pwd_and_full_oldpwd(char *new_pwd,
										t_minishell *minish);
void		cd_precheck(char **arr, t_minishell *minish);
void		update_env_pwd(t_minishell *minish, int pos,
							char *cwd, char *temp);
void		update_env_oldpwd(t_minishell *minish);


/* LEXER */
int			lexer(t_node_info **node, char *str, int type, int i);
int			cmd_block(t_node_info **node, char *str, int type);
int			cmd_br_block(t_node_info **node, char *str, int type);
int			and_if_condition_block(t_node_info **node, char *str, int type,
				int i);
int			pipe_block(t_node_info **node, char *str, int type, int i);
int			br_block(t_node_info **node, char *str, int type);
t_bool		is_odd(int n);
int			check_round_br(char *str, int point);
int			check_quote(char *str, int point, int symbol);
int			first_char_is_br_space_excluded(char *str);
int			last_char_is_br_space_excluded(char *str);
void		check_inside_quotes(char *str, int *i, int *quote_type);
int			br_search(char *str);
int			redir_search(char *str);
int			put_info_cmd_node(t_node_info **info, char *str, int type);
int			put_info_and_or_pipe_node(t_node_info **info, char *str, int point,
				int type);
int			put_info_bracket_node(t_node_info **info, char *str, int type);
int			put_info_cmd_br_node(t_node_info **info, char *str, int type);
int			put_simple_cmd_node(t_node_info **info, char *str, int type);
char		*part_cmd(char *str, int *i, int type_of_quote);
int			mod_cmd_str_no_br(char *str, char **redir, int i, int j);

/* PARSER */
int			create_tree(char *str, t_node **root, int *hd_num,
				t_minishell *minish);
t_bool		create_node(t_node_info *info, t_node **root);
int			add_or_and_pipe_tree(t_node_info *info, t_node **root, int *hd_num,
				t_minishell *minish);
int			add_br(t_node_info *info, t_node **root, int *hd_num,
				t_minishell *minish);
int			add_cmd(t_node_info *info, t_node **root, int *hd_num,
				t_minishell *minish);
int			add_cmd_br(t_node_info *info, t_node **root, int *hd_num,
				t_minishell *minish);
t_and		*init_t_and(void);
t_or		*init_t_or(void);
t_pipe		*init_t_pipe(void);
t_bracket	*init_t_br(void);
t_cmd		*init_t_cmd(void);
t_cmd_br	*init_t_cmd_br(void);
t_redir		*init_t_redir(void);
void		free_tree(t_node **root);

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
int			build_array_before_wc(char ***arr, int i, int k, int j);

/* SIGNALS */
void		toggler(int mode);
void		signal_interceptor(int mode);

/* VALIDATE SYNTAX */
char		*validate_redirect(char *str, t_bool *status);
char		*validate_word(char *str, t_bool *status);
t_bool		string_is_empty(char *str);

#endif
