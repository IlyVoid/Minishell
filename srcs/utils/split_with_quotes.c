#include "../../includes/minishell.h"

static int skip_quotes(char *str);

char	**wrapper_split_quotes(char *str)
{
	char	**res;
	int 	i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		if (str[i] == SPCE || str[i] == HT)
			str[i] = SEPERATOR;
		else if (str[i] == D_QUOTE || str[i] == S_QUOTE)
			i += skip_quotes(str + i);
		i++;
	}
	res = ft_split(str, SEPERATOR);
	if (!res)
		return (NULL);
	return (res);
}

static int skip_quotes(char *str)
{
	int	i;

	i = 0;
	if (*str == D_QUOTE)
	{
		i++;
		while (str[i] != D_QUOTE)
			i++;
	}
	else if (*str == S_QUOTE)
	{
		i++;
		while (str[i] != S_QUOTE)
			i++;
	}
	return (i);
}