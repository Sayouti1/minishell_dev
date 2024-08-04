/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:20:12 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	close_and_dup(int to_dup, int fd, int to_close)
{
	close(to_close);
	if (fd != -99)
		dup2(to_dup, fd);
	close(to_dup);
}

void	swap_pipes(int *curr_pipes, int *prev_pipes)
{
	prev_pipes[0] = curr_pipes[0];
	prev_pipes[1] = curr_pipes[1];
}

void	not_first_cmd(int i, int *prev_pipes)
{
	if (i != 0)
		close_and_dup(prev_pipes[0], 0, prev_pipes[1]);
}

int	execute_pipes(int len, int i, t_command *tmp_cmd)
{
	int	prev_pipes[2];
	int	curr_pipes[2];

	while (++i < len)
	{
		if (i != 0)
			swap_pipes(curr_pipes, prev_pipes);
		if (i != len - 1 && pipe(curr_pipes))
			return (printf("ERROR IN pipe()\n"), 1);
		if (fork() == 0)
		{
			not_first_cmd(i, prev_pipes);
			if (i != len - 1)
				close_and_dup(curr_pipes[1], 1, curr_pipes[0]);
			exec_simple_cmd(tmp_cmd);
			exit(0);
		}
		if (i != 0)
			close_and_dup(prev_pipes[0], -99, prev_pipes[1]);
		tmp_cmd = tmp_cmd->next;
	}
	close_and_dup(curr_pipes[0], -99, curr_pipes[1]);
	while (i-- > 0)
		wait(&g_vars.exit_status);
	return (set_exit_status(g_vars.exit_status));
}
