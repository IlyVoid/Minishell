/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:48:26 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/29 14:01:35 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_n)
{
	t_list	*i;

	if (!lst || !new_n)
		return ;
	if (!*lst)
	{
		*lst = new_n;
		return ;
	}
	i = *lst;
	while (i->next)
		i = i->next;
	i->next = new_n;
}
