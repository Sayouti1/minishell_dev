#include "../../../include/include.h"

void	setup_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
void handle_ctrl_c()
{
	
}