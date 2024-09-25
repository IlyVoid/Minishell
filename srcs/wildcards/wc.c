/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:12:39 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:14:06 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wc(char ***arr)
{
	t_wc	wc;
	int		status;

	if (!if_asterix_in_arr(*arr, 0, 0))
		return (SUCCESS);
	status = allocate_temp_array(arr, &wc);
	if (status == MALLOC_ERR)
		return (MALLOC_ERR);
	if (status == SYS_ERROR)
		return (SYS_ERROR);
	status = fill_temp_array(arr, &wc);
	if (status == SYS_ERROR)
		return (SYS_ERROR);
	if (status == MALLOC_ERR)
		return (MALLOC_ERR);
	status = allocate_and_fill_expanded_array(&wc);
	if (status == MALLOC_ERR)
		return (MALLOC_ERR);
	ft_free_2d_array(*arr);
	ft_free_3d_array(wc.temp_arr, 1);
	*arr = wc.new_arr;
	return (SUCCESS);
}
