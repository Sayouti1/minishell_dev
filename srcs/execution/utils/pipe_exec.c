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

void	redirection_exec(t_command *cmd);
void	add_to_fds(int val)
{
	t_fd_collectors	*node;
	t_fd_collectors	*tmp;

	node = malloc(sizeof(t_fd_collectors));
	if (NULL == node)
		return ;
	node->fd = val;
	node->next = NULL;
	if (NULL == g_vars.fd_collectors)
		g_vars.fd_collectors = node;
	else
	{
		tmp = g_vars.fd_collectors;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}
void	close_file_ds()
{
	t_fd_collectors	*tmp;

	while (g_vars.fd_collectors)
	{
		tmp = g_vars.fd_collectors->next;
		close(g_vars.fd_collectors->fd);
		free(g_vars.fd_collectors);
		g_vars.fd_collectors = tmp;
	}
	g_vars.fd_collectors = NULL;
	
}

int	init_commands_fds(t_command *cmd, int len, int *curr_pipes, int *prev_pipes)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (i != 0)
			swap_pipes(curr_pipes, prev_pipes);
		if (i < len - 1 && pipe(curr_pipes))
			return (perror("minishell "), 1);
		printf("pipe[%d, %d]\n", curr_pipes[0], curr_pipes[1]);
		add_to_fds(curr_pipes[0]);
		add_to_fds(curr_pipes[1]);
		if (i != 0)
		{
			if (cmd->fd_in != 0)
				close(cmd->fd_in);
			cmd->fd_in = prev_pipes[0];
		}
		if (i != len - 1)
		{
			if (cmd->fd_out != 1)
				close(cmd->fd_out);
			cmd->fd_out = curr_pipes[1];
		}
		redirection_exec(cmd);
		++i;
		cmd = cmd->next;
	}
	return (0);
}

void	close_fds(t_command *cmd)
{
	if (cmd->prev)
	{
		close(cmd->prev->fd_out);
		if (cmd->prev->fd_in != 0)
			close(cmd->prev->fd_in);
	}
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
}

int	execute_pipes(int len, int i, t_command *cmd, int *pids)
{
	int			curr_pipes[2];
	int			prev_pipes[2];
	int			pid;

	init_commands_fds(cmd, len, curr_pipes, prev_pipes);
	i = 0;
	while (cmd)
	{
		pid = fork();
		g_vars.parent = 0;
		if (pid == 0)
		{
			execute_command(cmd, 1);
			close_file_ds();
			exit(g_vars.exit_status);
		}
		g_vars.parent = 1;
		pids[i] = pid;
		close_fds(cmd);
		cmd = cmd->next;
		i++;
	}
	return (0);
}

void	process_command(t_command *command)
{
	t_command	*tmp_cmd;
	pid_t		*pids;
	int			i;
	int			j;

	if (list_len(command) == 1)
		execute_command(command, 0);
	else
	{
		i = list_len(command);
		pids = malloc(sizeof(int) * (i));
		collect_garbage(pids);
		if (NULL == pids && printf("Error Allocating pids\n"))
			return ;
		tmp_cmd = command;
		execute_pipes(i, i, tmp_cmd, pids);
		j = 0;
		while (j < i)
		{
			waitpid(pids[j++], &g_vars.exit_status, 0);
			if (j == i)
				set_exit_status(g_vars.exit_status);
		}
	}
}
