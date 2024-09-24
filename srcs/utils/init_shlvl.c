/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:38:47 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 01:49:07 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_non_digits(char *str)
{
	t_bool	sign;

	sign = false;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		str++;
		sign = true;
	}
	if (!(*str >= '0' && *str <= '9') && sign)
		return (true);
	while (*str >= '0' && *str <= '9')
		str++;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str != NULL_TERM)
		return (true);
	return (false);
}

static int	init_shlvl_if_exists(int pos, char ***penv,
	int number, char *shlvl)
{
	char	*new_number;
	char	*temp;

	shlvl = ft_strrchr((*penv)[pos], EQUAL) + 1;
	if (check_non_digits(shlvl))
		number = 0;
	else
		number = ft_atoi(shlvl);
	if (number < 0)
		number = -1;
	else if (number > 998)
	{
		shlvl_warn_msg(number + 1);
		number = 0;
	}
	new_number = ft_itoa(number + 1);
	if (!new_number)
		return (MALLOC_ERR);
	temp = ft_strjoin("SHLVL=", new_number);
	free(new_number);
	if (!temp)
		return (MALLOC_ERR);
	free((*penv)[pos]);
	(*penv)[pos] = temp;
	return (SUCCESS);
}

int	init_var_if_none_exist(char ***penv, int i, char *var)
{
	int		len;
	char	**env_new;

	if (add_to_env_list_env_new(*penv, &env_new, &i,
			&len) == MALLOC_ERR)
		return (MALLOC_ERR);
	env_new[len] = ft_strdup(var);
	if (!env_new[len])
	{
		ft_free_2d_array(env_new);
		return (MALLOC_ERR);
	}
	*penv = env_new;
	return (SUCCESS);
}

int	init_shlvl(char ***penv)
{
	int		pos;
	int		status;

	status = 0;
	pos = env_var(*penv, "SHLVL=", -1, 6);
	if (pos == -1)
	{
		status = init_var_if_none_exist(penv, 1, "SHLVL=1");
		if (status != 0)
			return (status);
	}
	else
	{
		status = init_shlvl_if_exists(pos, penv, 0, NULL);
		if (status != 0)
			return (status);
	}
	return (status);
}
