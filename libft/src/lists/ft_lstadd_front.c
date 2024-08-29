/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:48:34 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/29 14:01:01 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_n)
{
	if (!(lst && new_n))
		return ;
	new_n->next = *lst;
	*lst = new_n;
}
