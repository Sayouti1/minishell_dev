/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:27 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:18:48 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	execute_bin(t_command *cmd)
{
	int	pid;

	g_vars.parent = 0;
	pid = fork();
	signal(SIGQUIT, sig_handler);
	if (0 == pid)
	{
		if (cmd->fd_in != 0)
			dup2(cmd->fd_in, 0);
		if (cmd->fd_out != 1)
			dup2(cmd->fd_out, 1);
		if (execve(cmd->command, cmd->args, get_env_array()) == -1)
		{
			perror("minishell ");
			if (errno == EACCES || errno == EISDIR)
				return (exit(126), 1);
			if (errno == ENOENT)
				return (exit(127), 1);
		}
		exit(1);
	}
	wait(&g_vars.exit_status);
	g_vars.parent = 1;
	set_exit_status(g_vars.exit_status);
	return (0);
}

void	redirection_exec(t_command *cmd)
{
	t_redirection	*tmp;

	tmp = cmd->redirection;
	while (tmp)
	{
		if (tmp->type == OUTPUT || tmp->type == APPEND)
			cmd->fd_out = tmp->fd;
		else if (tmp->type == INPUT)
			cmd->fd_in = tmp->fd;
		else if (tmp->type == HEREDOC && 0 == open_heredoc(tmp))
			cmd->fd_in = tmp->fd;
		tmp = tmp->next;
	}
}

int	is_directory(char *path)
{
	struct stat	dir_stat;

	stat(path, &dir_stat);
	return (S_ISDIR(dir_stat.st_mode));
}

void	execute_command(t_command *cmd, int piped)
{
	if (!piped)
		redirection_exec(cmd);
	if (g_vars.sig_c == 2 || check_redirection(cmd))
		return ;
	if (built_in(cmd->command))
		execute_built_in(cmd);
	else
	{
		if (NULL == cmd->command)
			g_vars.exit_status = 0;
		else if (fix_command_path(cmd))
			g_vars.exit_status = 127;
		else if (NULL == get_env_v1("PATH") && NULL == cmd->command)
			ft_perror(cmd->command, ": No such file or directory\n", NULL);
		else
		{
			if (is_directory(cmd->command)
				&& ft_perror("minishell ", cmd->command, ": Is a directory\n"))
				g_vars.exit_status = 126;
			else
				execute_bin(cmd);
		}
	}
}

int	fix_command_path(t_command *cmd)
{
	char	*cwd;
	char	*tmp_cmd;
	int		ret;

	ret = 0;
	tmp_cmd = cmd->command;
	cwd = getcwd(NULL, 0);
	cmd->command = get_full_path(cmd->command, cwd);
	if (NULL == cmd->command && ++ret)
	{
		ft_putstr_fd("minishell ", 2);
		ft_putstr_fd(tmp_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_vars.exit_status = 127;
	}
	free(cwd);
	free(tmp_cmd);
	if (cmd->command)
		fix_command_arg(cmd);
	return (ret);
}
