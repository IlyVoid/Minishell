/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:05:06 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 15:08:27 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

long	ft_atol(const char *str)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (ft_strncmp(str, "-9223372036854775808", ft_strlen(str)) == 0)
		return (LONG_MIN);
	if ((*str == '-' || *str == '+') && ft_isdigit(*(str + 1)))
	{
		sign = -1 * (*str == '-') + 1 * (*str == '+');
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		if ((SIZE_MAX / 10) < result
			|| ((SIZE_MAX / 10) == result && *str >= 54 && *str <= 57))
			return (0);
		result = result * 10 + (*str - 48);
		if ((sign == -1 && result > 0UL - LONG_MIN) || result > LONG_MAX)
			return (0);
		str++;
	}
	return ((long)sign * result);
}
