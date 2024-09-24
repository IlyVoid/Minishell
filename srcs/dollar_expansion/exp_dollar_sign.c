/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:21:25 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 20:28:43 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exp_dollar_sign(char **str, char **penv, int last_exit_status)
{
	if (generic_exp_dollar_sign(str, penv) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (q_mark_exp_dollar_sign(str, last_exit_status) == MALLOC_ERR)
		return (MALLOC_ERR);
	return (SUCCESS);
}
