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

/*
 * ✅ ❌Norminette
 */
// int	execute_command(char **split)
// {
// 	char	*fullpath;
// 	char	*curr_dir;
// 	pid_t	pid;
// 	char	**exec_arg;
//
// 	curr_dir = getcwd(NULL, 0);
// 	if (NULL == curr_dir && (split[0] && split[0][0] != '/'))
// 		return (printf("getcwd error!\n"), set_exit_status(1));
// 	fullpath = get_correct_path(split[0], curr_dir);
// 	free(curr_dir);
// 	if (NULL == fullpath)
// 		return (printf("COMMAND NOT FOUND : %s\n", split[0]),
// 			set_exit_status(127));
// 	if (access(fullpath, F_OK))
// 		return (printf("NO SUCH FILE OR DIRECTORY !!\n"), free(fullpath),
// 			set_exit_status(1));
// 	if (access(fullpath, X_OK))
// 		return (printf("PERMISSION DENIED : !!\n"), free(fullpath),
// 			set_exit_status(126));
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		exec_arg = get_exec_arg(fullpath, split[1]);
// 		if (NULL == exec_arg)
// 			return (1);
// 		if (execve(fullpath, exec_arg, g_vars.envp) == -1)
// 		{
// 			printf("CANNOT EXECUTE COMMAND : %s, [%s]\n", split[0], fullpath);
// 			free_split(exec_arg);
// 			set_exit_status(1);
// 			exit(1);
// 		}
// 	}
// 	else
// 		wait(&g_vars.exit_status);
// 	free(fullpath);
// 	return (set_exit_status(g_vars.exit_status));
// }

void	external_command(t_command *cmd)
{
	int	pid;

	pid = fork();
	if (0 == pid)
	{
		execve(cmd->command, cmd->args, g_vars.envp);
		printf("ERROR IN EXECVE EXTERNAL CMD\n");
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
	char			*cwd;
	char			*tmp_cmd;

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
		tmp_cmd = cmd->command;
		cwd = getcwd(NULL, 0);
		cmd->command = get_correct_path(cmd->command, cwd);
		free(cwd);
		free(tmp_cmd);
		fix_cmd_arg(cmd);
		external_command(cmd);
	}
}
