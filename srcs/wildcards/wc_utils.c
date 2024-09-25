/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:19:55 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 14:47:42 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	allocate_temp_array(char ***arr, t_wc *wc)
{
	int	i;

	i = 0;
	wc->arr_length = ft_arrlen((void **)(*arr));
	wc->ent_length = arr_len_entities(0);
	if (wc->ent_length == SYS_ERROR)
		return (SYS_ERROR);
	wc->temp_arr = ft_calloc(wc->arr_length + 1, sizeof(char **));
	if (!wc->temp_arr)
		return (MALLOC_ERR);
	while (i < wc->arr_length)
	{
		(wc->temp_arr)[i] = ft_calloc(arr_len_entities(0) + 1,
				sizeof(char *));
		if (!(wc->temp_arr)[i++])
		{
			ft_free_3d_array(wc->temp_arr, 0);
			return (MALLOC_ERR);
		}
	}
	return (SUCCESS);
}

int	fill_temp_array(char ***arr, t_wc *wc)
{
	int	i;

	i = -1;
	while (++i < wc->arr_length)
	{
		if (if_abs_path(wc, (*arr)[i]) == MALLOC_ERR)
		{
			ft_free_3d_array(wc->temp_arr, 0);
			return (MALLOC_ERR);
		}
		wc->status = exp_entity(&((wc->temp_arr)[i]), (*arr)[i], wc, NULL);
		if (wc->status == MALLOC_ERR)
		{
			ft_free_3d_array(wc->temp_arr, 0);
			return (MALLOC_ERR);
		}
		else if (wc->status == SYS_ERROR)
		{
			ft_free_3d_array(wc->temp_arr, 0);
			return (SYS_ERROR);
		}
		if (arr_sort_process(wc, &i) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}

int	allocate_and_fill_expanded_array(t_wc *wc)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	wc->arr_length = 0;
	while ((wc->temp_arr)[++i] != NULL)
		wc->arr_length += ft_arrlen((void **)(wc->temp_arr)[i]);
	wc->new_arr = ft_calloc(wc->arr_length + 1, sizeof(char *));
	if (!wc->new_arr)
	{
		ft_free_3d_array(wc->temp_arr, 0);
		return (MALLOC_ERR);
	}
	i = -1;
	while ((wc->temp_arr)[++j])
	{
		k = -1;
		while ((wc->temp_arr)[j][++k])
			(wc->new_arr)[++i] = (wc->temp_arr)[j][k];
	}
	return (SUCCESS);
}

static int	abs_path_check(t_wc *wc, char *str,
	int slash_cwd_len, int slash_str_len)
{
	char	*cwd;
	char	*cwd_join;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (MALLOC_ERR);
	cwd_join = ft_strjoin(cwd, "/");
	if (!cwd_join)
	{
		free(cwd);
		return (MALLOC_ERR);
	}
	slash_cwd_len = ft_strrchr(cwd_join, SLASH) - cwd_join + 1;
	if (slash_str_len > slash_cwd_len)
		slash_cwd_len = slash_str_len;
	if (str[0] == DOT && str[1] == SLASH)
		wc->abs_path_flag = DOT_PATH;
	else if (!ft_strncmp(cwd_join, str, slash_cwd_len))
		wc->abs_path_flag = ABS_PATH;
	free(cwd);
	free(cwd_join);
	return (SUCCESS);
}

int	if_abs_path(t_wc *wc, char *str)
{
	int		slash_str_len;
	int		slash_cwd_len;
	char	*temp;

	slash_str_len = 0;
	slash_cwd_len = 0;
	temp = ft_strrchr(str, SLASH);
	if (temp != NULL)
		slash_str_len = temp - str + 1;
	if (slash_str_len != 0 && ft_strlen(str) > 0)
	{
		if (abs_path_check(wc, str, slash_cwd_len,
				slash_str_len) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else
		wc->abs_path_flag = NO_PATH;
	return (SUCCESS);
}
