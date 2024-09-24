/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:44:06 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/23 23:26:51 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstdel_front(t_list **lst, void (*del)(void*))
{
	t_list	*new_top;

	if (!lst || !*lst)
		return ;
	new_top = (*lst)->next;
	del((*lst)->content);
	free(*lst);
	*lst = new_top;
}
