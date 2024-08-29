#include "../../includes/minishell.h"

t_bool	string_is_empty(char *str)
{
	if (ft_strlen(str) == 0)
		return (true);
	while (ft_isspace(*str))
		str++;
	return (*str == NULL_TERM);
}