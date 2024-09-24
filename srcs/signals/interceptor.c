/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interceptor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:24:38 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 16:43:28 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Gives ability to use interactive cmds like Ctl-C,
it injects a new line into the terminal*/
static void	sigint_interactive(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\033[1A");
		g_sgnl = sig;
	}
}

// init interceptor
static void	init_interceptor(void (*first_handle)(int),
				void (*second_handle)(int))
{
	struct sigaction	sa;
	struct sigaction	sq;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&sq, 0, sizeof(sq));
	sa.sa_handler = first_handle;
	sq.sa_handler = second_handle;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&sq.sa_mask);
	sa.sa_flags = SA_RESTART;
	sq.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sq, NULL);
}

// finished signal interceptor
void	signal_interceptor(int mode)
{
	if (mode == DEFAULT)
		init_interceptor(SIG_DFL, SIG_DFL);
	else if (mode == INTERACTIVE)
		init_interceptor(sigint_interactive, SIG_IGN);
	else if (mode == HEREDOC)
		init_interceptor(SIG_DFL, SIG_IGN);
	else if (mode == IGNORE)
		init_interceptor(SIG_IGN, SIG_IGN);
}
