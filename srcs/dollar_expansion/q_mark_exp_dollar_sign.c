/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_mark_exp_dollar_sign.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:49:17 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 20:52:22 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expansion_qm(char *str, int *last_ind)
{
	int	i;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (str[i] != NULL_TERM)
	{
		if ((d_quote == 0 || d_quote == 1) && s_quote != 1 && str[i] == D_SIGN
			&& str[i + 1] == Q_MARK)
		{
			str[i] = NULL_TERM;
			str[i + 1] = NULL_TERM;
			*last_ind = *last_ind + i + 2;
			return (i);
		}
		index_quotes(str, i, &s_quote, &d_quote);
		i++;
	}
	return (NOT_EXPANDABLE);
}

static int	combine_new_str(t_ds *ds_q, char **str)
{
	ds_q->new_str = ft_calloc(ds_q->new_len_str, sizeof(char));
	if (!ds_q->new_str)
	{
		free(ds_q->mid);
		return (MALLOC_ERR);
	}
	ft_strlcat(ds_q->new_str, ds_q->first, ds_q->new_len_str);
	ft_strlcat(ds_q->new_str, ds_q->mid, ds_q->new_len_str);
	ft_strlcat(ds_q->new_str, ds_q->last, ds_q->new_len_str);
	free(ds_q->mid);
	free(*str);
	*str = ds_q->new_str;
	ds_q->last_ind = 0;
	return (SUCCESS);
}

int	q_mark_exp_dollar_sign(char **str, int last_exit_status)
{
	t_ds	ds_q;

	ds_q.last_ind = 0;
	ds_q.new_str = *str;
	while (expansion_qm(ds_q.new_str, &(ds_q.last_ind)) != NOT_EXPANDABLE)
	{
		ds_q.first = ds_q.new_str;
		ds_q.last = ds_q.new_str + ds_q.last_ind;
		ds_q.mid = ft_itoa(last_exit_status);
		if (!ds_q.mid)
			return (MALLOC_ERR);
		ds_q.new_len_str = ft_strlen(ds_q.first) + ft_strlen(ds_q.mid)
			+ ft_strlen(ds_q.last) + 1;
		if (combine_new_str(&ds_q, str) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}
