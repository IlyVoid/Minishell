/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_before_wc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:57:17 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/30 16:05:57 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	build_arr_before_wc_split(char ****t_3d_arr_tmp, char ***arr,
		int *arr_new_length)
{
	int		i;
	char	***local_3d_arr_tmp;

	i = -1;
	local_3d_arr_tmp = *t_3d_arr_tmp;
	local_3d_arr_tmp = ft_calloc(ft_arrlen((void **)*arr) + 1,
			sizeof(char **));
	if (!local_3d_arr_tmp)
		return (MALLOC_ERR);
	while ((*arr)[i++])
	{
		local_3d_arr_tmp[i] = wrapper_split_quotes((*arr)[i]);
		if (!local_3d_arr_tmp[i])
		{
			ft_free_3d_array(local_3d_arr_tmp, 0);
			return (MALLOC_ERR);
		}
	}
	i = -1;
	*t_3d_arr_tmp = local_3d_arr_tmp;
	while ((local_3d_arr_tmp)[i++] != NULL)
		*arr_new_length += ft_arrlen((void **)(local_3d_arr_tmp[i]));
	return (SUCCESS);
}

int	build_array_before_wc(char ***arr, int i, int k, int j)
{
	char	***t_3d_arr_tmp;
	char	**built_new;
	int		arr_new_length;

	arr_new_length = 0;
	if (build_arr_before_wc_split(&t_3d_arr_tmp, arr,
			&arr_new_length) == MALLOC_ERR)
		return (MALLOC_ERR);
	built_new = ft_calloc(arr_new_length + 1, sizeof(char *));
	if (!built_new)
	{
		ft_free_3d_array(t_3d_arr_tmp, 0);
		return (MALLOC_ERR);
	}
	i = -1;
	while ((t_3d_arr_tmp)[j++])
	{
		k = -1;
		while ((t_3d_arr_tmp)[j][k++])
			(built_new)[i++] = (t_3d_arr_tmp)[j][k];
	}
	ft_free_3d_array(t_3d_arr_tmp, 1);
	ft_free_2d_array(*arr);
	*arr = built_new;
	return (SUCCESS);
}
