#include "../../includes/minishell.h"

volatile sig_atomic_t	g_sgnl;

int main()
{
	t_minishell	*minish;
	int 		prev_status;

	signal_interceptor(IGNORE);
	toggler(IMPLICIT);
	printf("\033[2J\033[H");
	init_minish(&minish);
	run_minish(&minish);
	prev_status = minish->exit_status;
	rl_clear_hist();
	save_hst_file(minish);
	free_minish(minish);
	minish = NULL;
	return (prev_status);
}