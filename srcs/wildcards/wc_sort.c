/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:36:20 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:03:44 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**str_arr_join(char **arr, char *str)
{
	char	**joined_arr;
	int		len;
	int		i;

	i = -1;
	len = ft_arrlen((void **)arr);
	joined_arr = ft_calloc(len + 2, sizeof(char *));
	if (!joined_arr)
		return (NULL);
	joined_arr[0] = str;
	while (++i < len)
		joined_arr[i + 1] = arr[i];
	return (joined_arr);
}

int	sort_arr_with_cmd_inside(t_wc *wc, char ***arr)
{
	wc->new_sorted_arr = sort_str_arr(*arr + 1,
			ft_arrlen((void **)(*arr)) - 1);
	if (!wc->new_sorted_arr)
	{
		ft_free_3d_array(wc->temp_arr, 0);
		return (MALLOC_ERR);
	}
	wc->new_final_arr = str_arr_join(wc->new_sorted_arr, (*arr)[0]);
	if (!wc->new_final_arr)
	{
		ft_free_3d_array(wc->temp_arr, 0);
		ft_free_2d_array(wc->new_sorted_arr);
		return (MALLOC_ERR);
	}
	free(*arr);
	free(wc->new_sorted_arr);
	*arr = wc->new_final_arr;
	return (SUCCESS);
}

int	arr_sort_process(t_wc *wc, int *i)
{
	char	**sorted_arr;

	sorted_arr = sort_str_arr((wc->temp_arr)[*i],
			ft_arrlen((void **)((wc->temp_arr)[*i])));
	if (!sorted_arr)
	{
		ft_free_3d_array(wc->temp_arr, 0);
		return (MALLOC_ERR);
	}
	free((wc->temp_arr)[*i]);
	(wc->temp_arr)[*i] = sorted_arr;
	return (SUCCESS);
}
