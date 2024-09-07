/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:50:52 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/03 10:15:49 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

extern volatile sig_atomic_t	g_sgnl;


typedef struct dirent	t_dirent;

typedef struct	s_wc
{
	DIR			*dir;
	t_dirent	*entry;
	char		***temp_arr;
	char		**new_arr;
	char		**new_sorted_arr;
	char		**new_final_arr;
	int			arr_length;
	int			ent_length;
	int			status;
	int			abs_path_flag;
	bool		dot_ind;
}				t_wc;

typedef struct s_node
{
	int					type;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct s_node_info
{
	int					type;
	char				*left_str;
	char				*right_str;
}						t_node_info;

typedef struct s_pipe
{
	int					type;
	t_node				*left;
	t_node				*right;
}						t_pipe;

typedef struct	s_bracket
{
	int			type;
	t_node 		*left;
	t_node 		*right;
}				t_bracket;

typedef struct s_redir
{
	int					type;
	char				**redirs;
}						t_redir;

typedef struct	s_exp_dollar
{
	char	*part_env;
	int 	i;
	int 	j;
	int 	s_quote;
	int 	d_quote;
	int 	ind_last_part;
	int 	lst_pos_env;
}			t_exp_dollar;

typedef struct	s_ds
{
	char	*new_str;
	char	*first;
	char	*mid;
	char	*last;
	int 	new_len_str;
	int 	last_ind;
}			t_ds;

typedef struct	s_and
{
	int 	type;
	t_node	*left;
	t_node	*right;
}			t_and;

typedef struct	s_or
{
	int 	type;
	t_node	*left;
	t_node	*right;
}			t_or;

typedef struct	s_cmd
{
	int 	type;
	t_node	*redir;
	char	*cmd;
}			t_cmd;

typedef struct	t_cmd_br
{
	int 	type;
	t_node	*right;
	t_node	*left;
}			t_cmd_br;

#endif