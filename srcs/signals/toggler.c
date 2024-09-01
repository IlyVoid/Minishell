#include "../../includes/minishell.h"

void	toggler(int mode)
{
	struct termios	terminal;

	ft_bzero(&terminal, sizeof(terminal));
	tcgetattr(STDIN_FILENO, &terminal);
	if (mode)
		terminal.c_lflag |= ECHOCTL;
	else if (!mode)
		terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}