/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brsantsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:49:07 by brsantsc          #+#    #+#             */
/*   Updated: 2024/09/17 10:01:45 by brsantsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	put_info_cmd_node(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*redir;
	int			status;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	status = mod_cmd_str_no_br(str, &redir, 0, 0);
	if (status == -1)
	{
		free(node_info);
		return (-1);
	}
	node_info->left_str = redir;
	node_info->right_str = str;
	node_info->type = type;
	*info = node_info;
	return (1);
}

int	put_info_and_or_pipe_node(t_node_info **info, char *str, int point,
		int type)
{
	t_node_info	*node_info;

	if (type == T_AND || type == T_OR)
	{
		str[point] = NULL_TERM;
		str[point - 1] = NULL_TERM;
	}
	else
		str[point] = NULL_TERM;
	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	node_info->left_str = str;
	node_info->right_str = str + point + 1;
	node_info->type = type;
	*info = node_info;
	return (1);
}

int	put_info_bracket_node(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*first;
	char		*last;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	first = ft_strchr(str, O_ROUND);
	last = ft_strrchr(str, C_ROUND);
	*first = ' ';
	*last = '\0';
	node_info->left_str = str;
	node_info->right_str = NULL;
	node_info->type = type;
	*info = node_info;
	return (1);
}

int	put_info_cmd_br_node(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*first;
	char		*left;
	char		*redir;
	int			i;

	i = 0;
	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	left = part_cmd(str, &i, 0) + i;
	if (mod_cmd_str_no_br(left, &redir, 0, 0) == -1)
	{
		free(node_info);
		return (-1);
	}
	first = ft_strchr(str, O_ROUND);
	*first = ' ';
	node_info->left_str = redir;
	node_info->right_str = str;
	node_info->type = type;
	*info = node_info;
	return (1);
}

int	put_simple_cmd_node(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	node_info->left_str = NULL;
	node_info->right_str = str;
	node_info->type = type;
	*info = node_info;
	return (1);
}
