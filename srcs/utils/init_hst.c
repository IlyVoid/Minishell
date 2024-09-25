/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:49:41 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 19:35:42 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_hstfile(t_minishell **minish);

void	init_hst(t_minishell **minishell)
{
	t_minishell	*minish;

	minish = *minishell;
	minish->history_path = ft_strjoin(minish->pwd, "/.d-sh_history");
	if (!minish->history_path)
	{
		print_err_msg("History file not supported for current session", NULL);
		return ;
	}
	if (access(minish->history_path, F_OK) == 0)
		read_hstfile(minishell);
}

void	read_hstfile(t_minishell **minish)
{
	FILE	*file;
	char	*curr;

	curr = NULL;
	file = fopen((*minish)->history_path, "r");
	if (file == NULL)
	{
		perror_err_msg("initialization error for history",
			(*minish)->history_path);
		return ;
	}
	while (1)
	{
		curr = readline(NULL);
		if (curr == NULL)
			break ;
		add_bash_hst(curr, minish, 0);
		free(curr);
	}
	if (ferror(file))
	{
		ft_putstr_fd("\033[0;31md-sh:\033[0;0m error occured while"
			" reading history file",
			STDERR_FILENO);
	}
	fclose(file);
}
