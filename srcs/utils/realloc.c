/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:14:40 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 01:21:17 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cpy_env(char **penv)
{
	char	**env;
	int		len;
	int		i;

	i = 0;
	len = ft_arrlen((void **)penv);
	env = ft_calloc(len + 1, sizeof(char *));
	if (!env)
		return (NULL);
	while (i < len)
	{
		env[i] = ft_strdup(penv[i]);
		if (!env[i])
		{
			ft_free_2d_array((void *)env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
