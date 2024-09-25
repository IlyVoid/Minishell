/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_exp_dollar_sign.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:29:16 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 20:47:52 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_dollar_sign_in_str(char *str, char **penv,
		t_exp_dollar *dollar)
{
	dollar->j = dollar->i;
	while (ft_isenv(str[dollar->i], &(dollar->i)))
		(dollar->i)++;
	dollar->ind_last_part = dollar->i;
	dollar->lst_pos_env = search_env_exp_module(penv, str + dollar->j, -1,
			dollar->i - dollar->j);
	if (dollar->lst_pos_env != NOT_FOUND)
		dollar->part_env = penv[dollar->lst_pos_env] + dollar->i - dollar->j
			+ 1;
	else
		dollar->part_env = "\0";
	(dollar->j)--;
	str[(dollar->j)++] = NULL_TERM;
	while (ft_isenv(str[dollar->j], &(dollar->j)))
		str[(dollar->j)++] = NULL_TERM;
}

static void	init_s_dollar(t_exp_dollar *dollar, char **part_env,
		int *ind_last_part)
{
	dollar->i = 0;
	dollar->j = 0;
	dollar->lst_pos_env = 0;
	dollar->s_quote = 0;
	dollar->d_quote = 0;
	dollar->ind_last_part = *ind_last_part;
	dollar->part_env = *part_env;
}

static int	expansion(char *str, char **penv, char **part_env,
		int *ind_last_part)
{
	t_exp_dollar	dollar;

	init_s_dollar(&dollar, part_env, ind_last_part);
	while (str[dollar.i] != NULL_TERM)
	{
		if ((dollar.d_quote == 0 || dollar.d_quote == 1) && dollar.s_quote != 1
			&& str[dollar.i] == D_SIGN)
		{
			if (++(dollar.i) && ft_isenv(str[dollar.i], &(dollar.i)))
			{
				process_dollar_sign_in_str(str, penv, &dollar);
				*part_env = dollar.part_env;
				*ind_last_part = dollar.ind_last_part;
				return (dollar.lst_pos_env);
			}
			continue ;
		}
		index_quotes(str, dollar.i, &(dollar.s_quote), &(dollar.d_quote));
		(dollar.i)++;
	}
	return (NOT_EXPANDABLE);
}

int	generic_exp_dollar_sign(char **str, char **penv)
{
	t_ds	ds_g;

	ds_g.new_str = *str;
	ds_g.mid = NULL;
	while (expansion(ds_g.new_str, penv, &(ds_g.mid),
			&(ds_g.last_ind)) != NOT_EXPANDABLE)
	{
		ds_g.first = ds_g.new_str;
		ds_g.last = ds_g.new_str + ds_g.last_ind;
		ds_g.new_len_str = ft_strlen(ds_g.first) + ft_strlen(ds_g.mid)
			+ ft_strlen(ds_g.last) + 1;
		ds_g.new_str = ft_calloc(ds_g.new_len_str, sizeof(char));
		if (!ds_g.new_str)
			return (MALLOC_ERR);
		ft_strlcat(ds_g.new_str, ds_g.first, ds_g.new_len_str);
		ft_strlcat(ds_g.new_str, ds_g.mid, ds_g.new_len_str);
		ft_strlcat(ds_g.new_str, ds_g.last, ds_g.new_len_str);
		free(*str);
		*str = ds_g.new_str;
	}
	*str = ds_g.new_str;
	return (SUCCESS);
}
