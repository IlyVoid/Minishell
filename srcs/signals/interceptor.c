/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interceptor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:24:38 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/03 08:24:40 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Gives ability to use interactive cmds like Ctl-C, it injects a new line into the terminal.
static void	sigint_interactive(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line(); // Create me thee readline functions please.
		rl_replace_line("", 0);
		printf("\033[1A");
		g_sgnl = sig;
	}
}

// init interceptor
static void	init_interceptor(void (*first_handle)(int),
								void (*second_hand)(int));

// finished signal interceptor
void	signal_interceptor(int mode);
