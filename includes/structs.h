/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:50:52 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/29 13:58:28 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	dirent	t_dirent;

typedef struct	s_node
{
	int				type;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct	s_node_info
{
	int		type;
	char	*left_str;
	char	*right_str;
}		t_node_info;

typedef struct	s_pipe
{
	int		type;
	t_node	*left;
	t_node	*right;
}		t_pipe;

typedef struct	s_redir
{
	int		type;
	char	**redirs;
}		t_redir;

#endif
