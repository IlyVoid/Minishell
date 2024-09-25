/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minish.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:49:01 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:16:54 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fetch_cmdline(char **cmdline, t_minishell **minish);
void	check_sig(t_minishell **minish);
void	ft_readline(char **cmdline, char *prompt);

void	run_minish(t_minishell **minish)
{
	int		status;
	char	*cmdline;
	int		hd_num;

	while (true)
	{
		status = fetch_cmdline(&cmdline, minish);
		if (status != 0 && status != EOF)
			(*minish)->exit_status = status;
		if (status == EOF || status == MALLOC_ERR)
			break ;
		if (status == 0)
		{
			hd_num = 0;
			(*minish)->root = NULL;
			status = create_tree(cmdline, &((*minish)->root), &hd_num, *minish);
			if (status != 0)
				(*minish)->exit_status = status;
			if (status == 0)
				(*minish)->exit_status = tree_traverser(&((*minish)->root), *minish);
			free(cmdline);
		}
	}
}

int	fetch_cmdline(char **cmdline, t_minishell **minish)
{
	int		status;
	char	*prompt;

	status = fetch_prompt(&prompt, (*minish)->exit_status);
	if (status != 0)
		return (status);
	ft_readline(cmdline, prompt);
	if (*cmdline == NULL)
	{
		if (handle_ctl_d(prompt) == MALLOC_ERR)
			handle_ctl_d_error("Ctrl+d error occured.\n");
		return (EOF);
	}
	free(prompt);
	if (ft_strlen(*cmdline) == 0)
	{
		free(*cmdline);
		check_sig(minish);
		return (fetch_cmdline(cmdline, minish));
	}
	add_bash_hst(*cmdline, minish, 1);
	status = input_val(*cmdline);
	if (status != 0)
		free(*cmdline);
	return (status);
}

void	check_sig(t_minishell **minish)
{
	if (g_sgnl == SIGINT)
	{
		(*minish)->exit_status = 1;
		g_sgnl = 0;
	}
}

void	ft_readline(char **cmdline, char *prompt)
{
	signal_interceptor(INTERACTIVE);
	toggler(IMPLICIT);
	*cmdline = readline(prompt);
	signal_interceptor(IGNORE);
}
