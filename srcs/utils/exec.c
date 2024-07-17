/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:27 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:31 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

char	*ft_strjoin_prefixed(char *s1, char c, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (NULL == s1 || NULL == s2)
		return (NULL);
	i = (int)ft_strlen(s1) + (int)ft_strlen(s2) + 2;
	join = (char *)malloc(sizeof(char) * i--);
	if (NULL == join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		join[j++] = s1[i++];
	join[j++] = c;
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}

/*
 * ✅ ❌Norminette
 */
int	execute_command(char **split)
{
	char	*fullpath;
	char	*curr_dir;
	pid_t	pid;
	char	**exec_arg;

	curr_dir = getcwd(NULL, 0);
	if (NULL == curr_dir && (split[0] && split[0][0] != '/'))
		return (printf("getcwd error!\n"), set_exit_status(1));
	fullpath = get_correct_path(split, curr_dir);
	free(curr_dir);
	if (NULL == fullpath)
		return (printf("COMMAND NOT FOUND : %s\n", split[0]), set_exit_status(127));
	if (access(fullpath, F_OK))
		return (printf("NO SUCH FILE OR DIRECTORY !!\n"), free(fullpath), set_exit_status(1));
	if (access(fullpath, X_OK))
		return (printf("PERMISSION DENIED : !!\n"), free(fullpath), set_exit_status(126));
	pid = fork();
	if (pid == 0)
	{
		exec_arg = get_exec_arg(fullpath, split[1]);
		if (NULL == exec_arg)
			return (1);
		if (execve(fullpath, exec_arg, g_vars.envp) == -1)
		{
			printf("CANNOT EXECUTE COMMAND : %s, [%s]\n", split[0], fullpath);
			free_split(exec_arg);
			set_exit_status(1);
			exit(1);
		}
	}
	else
		wait(&g_vars.exit_status);
	free(fullpath);
	return (set_exit_status(g_vars.exit_status));
}

void	execute_built_in(char **arg)
{
	if (!ft_strcmp(arg[0], "echo"))
	{
		if (arg[1])
			ft_echo(arg[1]);
		else
			printf("\n");
		set_exit_status(0);
	}
	else if (!ft_strcmp(arg[0], "cd"))
		cd(arg);
	else if (!ft_strcmp(arg[0], "pwd"))
		pwd();
	else if (!ft_strcmp(arg[0], "export"))
	{
		if (arg[1])
			ft_export(arg[1]);
		else
			ft_print_export();
	}
	else if (!ft_strcmp(arg[0], "unset"))
	{
		if (arg[1])
			ft_unset(arg[1]);
	}
	else if (!ft_strcmp(arg[0], "env"))
	{
		if (NULL == arg[1])
			ft_env();
		else
			set_exit_status(127);
	}
	else if (!ft_strcmp(arg[0], "exit"))
		ft_exit(arg[1]);
}

/*
 * TO BE FIXED
 */
int	execute_pipes(char **pipes)
{
	int	i;
	int	prev_pipes[2];
	int	curr_pipes[2];

	i = 0;
	while (i < split_len(pipes))
	{
		if (i != 0)
		{
			prev_pipes[0] = curr_pipes[0];
			prev_pipes[1] = curr_pipes[1];
		}
		if (i != split_len(pipes) - 1)
			if (pipe(curr_pipes))
				return (printf("ERROR IN pipe()\n"), 1);
		if (fork() == 0)
		{
			if (i != 0)
			{
				close(prev_pipes[1]);
				dup2(prev_pipes[0], 0);
				close(prev_pipes[0]);
			}
			if (i != split_len(pipes) - 1)
			{
				close(curr_pipes[0]);
				dup2(curr_pipes[1], 1);
				close(curr_pipes[0]);
			}
			exec_simple_cmd(pipes[i]);
			exit(0);
		}
		else
		{
			if (i != 0)
			{
				close(prev_pipes[0]);
				close(prev_pipes[1]);
			}
		}
		++i;
	}
	close(curr_pipes[0]);
	close(curr_pipes[1]);
	while (i-- > 0)
		wait(&g_vars.exit_status);
	return (set_exit_status(g_vars.exit_status));
}

void	exec_simple_cmd(char *cmd)
{
	char	**split;
	int		redirect;

	split = split_on_two(cmd, " \t");
	redirect = has_redirect(split[1]);
	if (redirect == 1 || redirect == 2)
    {
        redirect_to_file(cmd, split[1], redirect - 1);
        free_split(split);
        return ;
    }
	if (built_in(split[0]))
		execute_built_in(split);
	else
		execute_command(split);
	free_split(split);
}
