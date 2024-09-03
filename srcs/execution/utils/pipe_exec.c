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

void	swap_pipes(int *curr_pipes, int *prev_pipes)
{
	prev_pipes[0] = curr_pipes[0];
	prev_pipes[1] = curr_pipes[1];
}

int	init_commands_fds(t_command *cmd, int len, int *curr_pipes, int *prev_pipes)
{
	int i;

	i = 0;
	while (cmd)
	{
		if (i != 0)
			swap_pipes(curr_pipes, prev_pipes);
		if (i < len - 1 && pipe(curr_pipes))
			return (perror("minishell "), 1);
		if (i != 0)
			cmd->fd_in = prev_pipes[0];
		if (i != len -1)
			cmd->fd_out = curr_pipes[1];
		++i;
		cmd = cmd->next;
	}
	return (0);
}

int	execute_pipes(int len, int i, t_command *cmd)
{
	t_command	*tmp;
	int 		curr_pipes[2];
	int			prev_pipes[2];

	tmp = cmd;
	if (init_commands_fds(cmd, len, curr_pipes, prev_pipes))
		return (1);
	while (tmp)
	{
		if (fork() == 0)
		{
			execute_command(tmp);
			exit(g_vars.exit_status);
		}
		if (tmp->fd_out != 1)
			close (tmp->fd_out);
		if (tmp->fd_in != 0)
			close (tmp->fd_in);
		tmp = tmp->next;
	}
	close(curr_pipes[1]);
	close(curr_pipes[0]);
	while (i-- > 0)
		wait(&g_vars.exit_status);
	return (0);
}

void		process_command(t_command *command)
{
	t_command	*tmp_cmd;
	int			i;


	if (list_len(command) == 1)
		execute_command(command);
	else
	{
		i = -1;
		tmp_cmd = command;
		execute_pipes(list_len(command), i, tmp_cmd);
	}
}
