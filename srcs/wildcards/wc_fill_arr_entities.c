/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_fill_arr_entities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:25 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:03:37 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	auxiliary_closedir(t_wc *wc)
{
	closedir(wc->dir);
	return (MALLOC_ERR);
}

static int	dot_path_const_wc_block(t_wc *wc, char **temp_arr_local, char *str,
		int *i)
{
	char	*first;

	if (wc_strcmp(wc->entry->d_name, str + 2))
	{
		first = "./";
		temp_arr_local[*i] = ft_strjoin(first, wc->entry->d_name);
		if (!temp_arr_local[(*i)++])
			return (auxiliary_closedir(wc));
	}
	return (SUCCESS);
}

static int	abs_path_const_wc_block(t_wc *wc, char **temp_arr_local, char *str,
		int *i)
{
	char	*first;
	char	*second;

	if (wc_strcmp(wc->entry->d_name, ft_strrchr(str, SLASH) + 1))
	{
		first = getcwd(NULL, 0);
		if (!first)
			return (auxiliary_closedir(wc));
		second = ft_strjoin(first, "/");
		free(first);
		if (!second)
			return (auxiliary_closedir(wc));
		temp_arr_local[*i] = ft_strjoin(second, wc->entry->d_name);
		free(second);
		if (!temp_arr_local[(*i)++])
			return (auxiliary_closedir(wc));
	}
	return (SUCCESS);
}

static int	no_path_wc_block(t_wc *wc, char **temp_arr_local, char *str, int *i)
{
	if (wc_strcmp(wc->entry->d_name, str))
	{
		temp_arr_local[*i] = ft_strdup(wc->entry->d_name);
		if (!temp_arr_local[(*i)++])
		{
			closedir(wc->dir);
			return (MALLOC_ERR);
		}
	}
	return (SUCCESS);
}

int	fill_temp_arr_conditions_block(t_wc *wc, char **temp_arr_local, char *str,
		int *i)
{
	if (wc->abs_path_flag == DOT_PATH)
	{
		if (dot_path_const_wc_block(wc, temp_arr_local, str, i) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else if (wc->abs_path_flag == ABS_PATH)
	{
		if (abs_path_const_wc_block(wc, temp_arr_local, str, i) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else
	{
		if (no_path_wc_block(wc, temp_arr_local, str, i) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}
