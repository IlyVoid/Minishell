/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:06:15 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/23 15:33:19 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	apply_redirect(char *redir, t_minishell *minish, int *in, int *out);
int	replace_fd(int in, int out);

int	apply_redirects(char **redirs, t_minishell *minish)
{
	int	i;
	int	status;
	int	in;
	int	out;

	in = 1;
	out = -1;
	status = 0;
	i = 0;
	while (redirs[i] && status == 0)
	{

	}
}
