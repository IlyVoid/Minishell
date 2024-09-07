#include "../../includes/minishell.h"

int tree_traverser(t_node **root, t_minishell *minish)
{
	int type;
	int status;

	status = true;
	type = (*root)->type;
	if (type == T_AND)
		status = and_traverser(root, minish);
	else if (type == T_OR)
		status = or_traverser(root, minish);
	else if (type == T_PIPE)
		status = pipe_traverser(root,  minish);
	else if (type == T_BRACKET)
		status = bracket_traverser(root, minish);
	else if (type == T_CMD_BR)
		status = cmd_br_traverser(root, minish);
	else if (type == T_CMD)
		status = 
}