/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brsantsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:37:07 by brsantsc          #+#    #+#             */
/*   Updated: 2024/09/24 16:30:04 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_minish(t_minishell *minish)
{
	if (!minish)
		return ;
	if (minish->env)
		ft_free_2d_array(minish->env);
	if (minish->pwd)
		free(minish->pwd);
	if (minish->oldpwd)
		free(minish->oldpwd);
	if (minish->history_path)
		free(minish->history_path);
	if (minish->history)
		ft_lstclear(&(minish->history), free);
	if (minish->root)
		free_tree(&(minish->root));
	free(minish);
}
