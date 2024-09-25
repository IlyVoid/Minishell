/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_exp_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:48:50 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:04:00 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fill_temp_arr_with_str(char *str, char **temp_arr_local, t_wc *wc)
{
	int	i;

	i = 0;
	while (wc->entry != NULL && i < wc->ent_length)
	{
		if (wc->entry->d_name[0] == '.' && wc->dot_ind == false)
		{
			wc->entry = readdir(wc->dir);
			continue ;
		}
		if (fill_temp_arr_conditions_block(wc, temp_arr_local, str,
				&i) == MALLOC_ERR)
			return (MALLOC_ERR);
		wc->entry = readdir(wc->dir);
	}
	return (SUCCESS);
}

static int	fill_empty_arr(char **temp_arr_local, char *str)
{
	if (ft_arrlen((void **)temp_arr_local) == 0)
	{
		temp_arr_local[0] = ft_strdup(str);
		if (!temp_arr_local[0])
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}

int	exp_entity(char ***temp_arr, char *str, t_wc *wc, char **local)
{
	char	*slash_searcher;

	local = *temp_arr;
	slash_searcher = ft_strrchr(str, SLASH);
	wc->dot_ind = false;
	if ((slash_searcher != NULL && slash_searcher[1] == '.')
		|| (slash_searcher == NULL && str[0] == '.'))
		wc->dot_ind = true;
	wc->dir = opendir(".");
	if (wc->dir == NULL)
	{
		perror("Unable to open directory");
		return (SYS_ERROR);
	}
	wc->entry = readdir(wc->dir);
	if (fill_temp_arr_with_str(str, local, wc) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (closedir(wc->dir) == SYS_ERROR)
	{
		perror("Unable to close directory");
		return (SYS_ERROR);
	}
	if (fill_empty_arr(local, str) == MALLOC_ERR)
		return (MALLOC_ERR);
	return (SUCCESS);
}
