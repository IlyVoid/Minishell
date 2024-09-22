/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:25:03 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 16:34:59 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <unistd.h>

static void	cd_old_pwd_handler(t_minishell *minish)
{
	int	env_vars;

	env_vars = env_var(minish->env, "OLDPWD=", -1, 7);
	if (env_vars == -1)
	{
		print_err_msg("cd: ", "OLDPWD not set\n");
		minish->exit_status = GENERIC_ERROR;
		return ;
	}
	else if (chdir((minish->env)[env_vars] + 7) != 0)
	{
		perror_err_msg("cd: ", (minish->env)[env_vars] + 7);
		minish->exit_status = GENERIC_ERROR;
		return ;
	}
	else
		printf("%s\n", (minish->env)[env_vars] + 7);
}


