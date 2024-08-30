/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_3d_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:07:13 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/30 14:12:31 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_free_2d_array(void *ptr)
{
	void	**arr;
	size_t	i;

	arr = (void **)ptr;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_free_3d_array(void *ptr, int mode)
{
	void	***arr;
	void	(*f)(void *);
	size_t	i;

	if (mode == 0)
		f = ft_free_2d_array;
	else
		f = free;
	arr = (void ***)ptr;
	i = 0;
	while (arr[i])
		f(arr[i++]);
	free(arr);
}
