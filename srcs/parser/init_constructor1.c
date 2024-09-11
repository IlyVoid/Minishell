#include "../../includes/minishell.h"

t_cmd_br	*init_t_cmd_br()
{
	t_cmd_br	*node;

	node = (t_cmd_br *)ft_calloc(1, sizeof(t_cmd_br));
	if (!node)
		return (NULL);
	node->type = T_CMD_BR;
	return (node);
}

t_redir	*init_t_redir()
{
	t_redir	*node;

	node = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = T_REDIR;
	return (node);
}