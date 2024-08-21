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

void	external_command(t_command *cmd)
{
	int	pid;

	pid = fork();
	if (0 == pid)
	{
		execve(cmd->command, cmd->args, g_vars.envp);
		exit(1);
	}
	wait(&g_vars.exit_status);
	set_exit_status(g_vars.exit_status);
}

char	*get_dollar_key_v1(char *line, int *i)
{
	int		j;
	int		k;
	char	*key;

	j = *i + 1;
	if (NULL == line)
		return (NULL);
	while (line[j] && !ft_char_in(line[j], " $\'\"\n{}"))
		j++;
	key = (char *)malloc(sizeof(char) * (j - *i));
	if (NULL == key)
		return (NULL);
	k = 0;
	(*i)++;
	while (*i < j && line[*i])
		key[k++] = line[(*i)++];
	key[k] = '\0';
	return (key);
}

void	exec_simple_cmd(t_command *cmd)
{
	t_redirection	*tmp;

	tmp = cmd->redirection;
	while (tmp)
	{
		if (tmp->type == OUTPUT || tmp->type == APPEND)
			dup2(tmp->fd, 1);
		else if (tmp->type == INPUT)
			dup2(tmp->fd, 0);
		else if (tmp->type == HEREDOC)
			open_heredoc(tmp);
		close(tmp->fd);
		tmp = tmp->next;
	}
	if (built_in(cmd->command))
		execute_built_in(cmd);
	else
	{
		if (NULL == get_env_v1("PATH") && reset_fd())
			printf("%s: No such file or directory\n", cmd->command);
		else if (fix_command_path(cmd))
			set_exit_status(127);
		else
			external_command(cmd);
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
	cmd->command = get_correct_path(cmd->command, cwd);
	if (NULL == cmd->command && ++ret && reset_fd())
		printf("%s: command not found\n", tmp_cmd);
	free(cwd);
	free(tmp_cmd);
	if (cmd->command)
		fix_cmd_arg(cmd);
	return (ret);
}
