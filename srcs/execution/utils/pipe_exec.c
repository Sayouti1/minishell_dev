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
		printf("[%s]=>[%d,%d]\n", cmd->command, cmd->fd_in, cmd->fd_out);
		cmd = cmd->next;
	}
	return (0);
}


int execute_pipes(int len, int i, t_command *cmd)
{
    int curr_pipes[2];
    int prev_pipes[2];

	init_commands_fds(cmd, len, curr_pipes, prev_pipes);
	i = 0;
	while (cmd)
	{
		int pid = fork();
		if (pid == 0)
		{
			execute_command(cmd);
			exit(g_vars.exit_status);
		}
		if (cmd->prev)
		{
			close(cmd->prev->fd_out);
			if (cmd->prev->fd_in != 0)
				close(cmd->prev->fd_in);
		}
		if (cmd->fd_in != 0) close(cmd->fd_in);
		if (cmd->fd_out != 1) close(cmd->fd_out);
		cmd = cmd->next;
		i++;
	}
	while (i-- > 0 && printf("%d => [%d]\n", i, g_vars.exit_status))
		wait(&g_vars.exit_status);
    return 0;
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
