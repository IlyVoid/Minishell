/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:07:13 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/29 14:07:15 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void    ft_free_2d_array(void *ptr)
{
	void    **arr;
	size_t  i;

	arr = (void**)ptr;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
