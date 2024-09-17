/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brsantsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:28:37 by brsantsc          #+#    #+#             */
/*   Updated: 2024/09/17 09:36:48 by brsantsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_sgnl;

int	main(void)
{
	t_minishell	*minish;
	int			prev_status;

	signal_interceptor(IGNORE);
	toggler(IMPLICIT);
	printf("\033[2J\033[H");
	init_minish(&minish);
	run_minish(&minish);
	prev_status = minish->exit_status;
	rl_clear_hist();
	save_hst_file(minish);
	free_minish(minish);
	minish = NULL;
	return (prev_status);
}
