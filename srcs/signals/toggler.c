/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brsantsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:37 by brsantsc          #+#    #+#             */
/*   Updated: 2024/09/16 09:44:42 by brsantsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	toggler(int mode)
{
	struct termios	terminal;

	ft_bzero(&terminal, sizeof(terminal));
	tcgetattr(STDIN_FILENO, &terminal);
	if (mode)
		terminal.c_lflag |= ECHOCTL;
	else if (!mode)
		terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}
