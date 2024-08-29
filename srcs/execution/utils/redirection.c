/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:33:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/14 20:34:53 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

t_redirection	*new_redirection(int type, char *file_name, int fd, int creat_file)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (NULL == redirection)
		return (NULL);
	redirection->type = type;
	redirection->file_name = file_name;
	if (type != HEREDOC && NULL == file_name)
		fd = -1337;
	else if (type == OUTPUT && creat_file)
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	else if (type == APPEND && creat_file)
		fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0666);
	else if (type == INPUT && NULL != file_name)
		fd = open(file_name, O_RDONLY);
	else if (type == HEREDOC)
		redirection->file_name = file_name;
	redirection->fd = fd;
	redirection->next = NULL;
	return (redirection);
}

t_command	*new_command(char *command, char **args, t_redirection *redirection)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (NULL == cmd)
		return (NULL);
	cmd->command = command;
	cmd->args = args;
	cmd->redirection = redirection;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	add_to_cmds(t_command **head, t_command *cmd)
{
	t_command	*tmp;

	if (*head == NULL)
	{
		*head = cmd;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	if (cmd)
		cmd->prev = tmp;
	tmp->next = cmd;
}

char	**fix_cmd_arg(t_command *cmd)
{
	char	**new_arg;
	int		i;

	new_arg = (char **)malloc(sizeof(char *) * (split_len(cmd->args) + 2));
	if (NULL == new_arg)
		return (NULL);
	new_arg[0] = ft_strdup(cmd->command);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_arg[i + 1] = ft_strdup(cmd->args[i]);
		++i;
	}
	new_arg[i + 1] = NULL;
	free_split(cmd->args);
	cmd->args = new_arg;
	return (new_arg);
}
