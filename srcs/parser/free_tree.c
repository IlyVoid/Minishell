#include "../../includes/minishell.h"

void	free_tree(t_node **root)
{
	if (*root == NULL)
		return ;
	if ((*root)->type == T_BRACKET)
	{
		if ((*root)->left)
			free_tree(&((*root)->left));
	}
	else if ((*root)->type == T_REDIR)
	{
		if (((t_redir *)(*root))->redirs)
			ft_free_2d_array(((t_redir *)(*root))->redirs);
	}
	else if ((*root)->type == T_CMD)
	{
		free_tree(&((t_cmd *)(*root))->redir);
	}
	else
	{
		if ((*root)->left)
			free_tree(&((*root)->left));
		if ((*root)->right)
			free_tree(&((*root)->right));
	}
	free(*root);
	*root = NULL;
}