/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_nl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:00:38 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 17:01:16 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_remove_nl(char *str)
{
	int			len;

	len = ft_strlen(str);
	if (len == 0)
		return ;
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}
