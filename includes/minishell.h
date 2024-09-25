/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:35:44 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:14:01 by quvan-de         ###   ########.fr       */
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

/* MINISHELL */
int			fetch_cmdline(char **cmdline, t_minishell **minish);
void		check_sig(t_minishell **minish);
void		run_minish(t_minishell **minish);
void		ft_readline(char **cmdline, char *prompt);
void		kill_minish(t_minishell **minish, int status);
void		init_minish(t_minishell **minish);
void		free_minish(t_minishell *minish);

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
int			cmd_run(char **arr, t_minishell *minish, int cmd_type);
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
void		create_ops_array(char **arr, char **penv, int *ops);
int			check_ops(int *ops, int *i, int *j, int type);
int			add_to_env_list_env_new(char **penv, char ***result,
									int *i, int *len);
int			add_to_env_list(char ***env_new, char **arr,
							t_minishell *minish, int *ops);
int			edit_env_list(char ***env_new, char **arr, int *ops,
						t_minishell *minish);
int			check_for_errors(char **arr, int *ops);
int			exec_other(char **arr, int *ops);
void		run_export(char **arr, t_minishell *minish);

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

/* RL */
void		rl_clear_history(void);
void		rl_replace_line(const char *text, int clear_undo);

/* UTILS */
void		remove_quotes(char *str, int i, int j);
void		remove_quotes_arr(char **arr, int i);
void		syntax_err_msg(char *str);
void		print_err_msg(char *cmd, char *msg);
void		perror_err_msg(char *cmd, char *arg);
void		arg_err_msg(char *cmd, char *arg, char *msg);
void		shlvl_warn_msg(int number);
void		handle_ctl_d_error(char *msg);
int			handle_ctl_d(char *prompt);
char		**wrapper_split_quotes(char *str);
int			build_array_before_wc(char ***arr, int i, int k, int j);
void		add_bash_hst(char *cmdline, t_minishell **minishell, int mode);
void		add_to_hst_lst(char *cmd, char *cmdline, t_minishell **minishell);
void		err_hst(char *cmd);
void		init_hst(t_minishell **minishell);
void		read_hstfile(t_minishell **minish);
int			prompt_builder(char *dir_name, char **prompt, char *exit_status);
int			fetch_prompt(char **prompt, int exit_status);
int			init_pwd(char ***penv, char **pwd);
char		**cpy_env(char **penv);
void		save_hst_file(t_minishell *minish);
void		lst_write(void *str);
int			check_non_digits(char *str);
int			init_var_if_none_exist(char ***penv, int i, char *var);
int			init_shlvl(char ***penv);
char		**sort_str_arr(char **av, int size);

/* SIGNALS */
void		toggler(int mode);
void		signal_interceptor(int mode);

/* EXP DOLLAR */
int			exp_dollar_sign(char **str, char **penv, int last_exit_status);
int			generic_exp_dollar_sign(char **str, char **penv);
int			q_mark_exp_dollar_sign(char **str, int last_exit_status);
int			search_env_exp_module(char **penv, char *var, int i, int j);
void		index_quotes(char *str, int i, int *s_quote, int *d_quote);

/* WILDCARDS */
int			allocate_temp_array(char ***arr, t_wc *wc);
int			fill_temp_array(char ***arr, t_wc *wc);
int			allocate_and_fill_expanded_array(t_wc *wc);
int			if_abs_path(t_wc *wc, char *str);
int			arr_sort_process(t_wc *wc, int *i);
int			sort_arr_with_cmd_inside(t_wc *wc, char ***arr);
char		**str_arr_join(char **arr, char *str);
int			fill_temp_arr_conditions_block(t_wc *wc,
							char **temp_arr_local, char *str, int *i);
int			fill_temp_arr_with_str(char *str, char **temp_arr_local, t_wc *wc);
int			exp_entity(char ***temp_arr, char *str, t_wc *wc, char **local);
int			arr_len_entities(int sub_arr_len);
t_bool		trans_str_back(char *line, char *pattern, t_bool res);
void		trans_str(char *line, char *pattern);
t_bool		if_only_asterix(char *pattern);
t_bool		wc_strcmp(char *line, char *pattern);
t_bool		if_asterix_in_arr(char **arr, int i, int j);
int			wc(char ***arr);

/* VALIDATE SYNTAX */
char		*pipe_val(char *str, t_bool *status);
char		*cmd_val(char *str, t_bool *status);
char		*simple_cmd_val(char *str, t_bool *status);
char		*redir_val(char *str, t_bool *status);
char		*word_val(char *str, t_bool *status);
char		*and_or_val(char *str, t_bool *status);
t_bool		string_is_empty(char *str);
int			input_val(char *str);

#endif
