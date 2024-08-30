/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:43:34 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/29 14:04:43 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_isalnum(int i)
{
	if (('0' <= i && i <= '9') || ('A' <= i && i <= 'Z') || ('a' <= i
			&& i <= 'z'))
		return (1);
	return (0);
}
