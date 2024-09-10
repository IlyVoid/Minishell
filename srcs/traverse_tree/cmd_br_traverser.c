#include "../../includes/minishell.h"

int	cmd_br_traverser(t_node **root, t_minishell *minish)
{
	int status;
	pid_t pid;
	t_node *node;

	if (minish->is_parent == false)
		signal_interceptor(DEFAULT);
	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		signal_interceptor(DEFAULT);
		minish->is_parent = false;
		node = *root;
		status = apply_redirects(((t_redir *)(node->left))->redirs, minish);
		if (status == 0)
			status = tree_traversal(&(node->right), minish);
		exit(status);
	}
	else
		status = wait_childs(&pid, 1);
	return (status);
}