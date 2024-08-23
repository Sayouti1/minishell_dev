/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:34:46 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	get_start_end(char *str, int *s, int *e)
{
	int	end;
	int	start;

	if (NULL == str)
		return ;
	start = 0;
	while (str && str[start] && str[start] == '\'' && str[start + 1] == str[start])
		start += 2;
	while (str && str[start] && str[start] == '"' && str[start + 1] == str[start])
		start += 2;
	end = ft_strlen(str) - 1;
	while (end > 0 && str[end] == '\'' && str[end - 1] == str[end])
		end -= 2;
	while (end > 0 && str[end] == '"' && str[end - 1] == str[end])
		end -= 2;
	if (end < 0)
		end = 0;
	*s = start;
	*e = end;
}

char *trim_and_reallocate_str(char *str, int start, int end)
{
	char	*tmp;
	int		i;

	if (start >= end)
		return (NULL);
	tmp = malloc((end - start + 2) * sizeof(char));
	if (NULL == tmp)
		return (NULL);
	i = 0;
	while (start <= end)
		tmp[i++] = str[start++];
	tmp[i] = '\0';
	return (tmp);
}

int	remove_edge_quotes(t_command *cmd)
{
	char		*tmp;
	int			start;
	int			end;
	int			i;

	tmp = cmd->command;
	get_start_end(cmd->command, &start, &end);
	if (start > end)
		return (1);
	cmd->command = malloc((end - start + 2) * sizeof(char));
	if (NULL == cmd->command)
		return (free(tmp), 1);
	i = 0;
	while (start <= end)
		cmd->command[i++] = tmp[start++];
	cmd->command[i] = '\0';
	free(tmp);
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		tmp = cmd->args[i];
		get_start_end(cmd->args[i], &start, &end);
		cmd->args[i] = trim_and_reallocate_str(cmd->args[i], start, end);
	}
	return (0);
}

void	remove_double_quotes_middle(t_command *cmd)
{
	char 	*new_cmd;
	char 	*tmp_cmd;
	int		i;

	if (NULL == cmd || NULL == cmd->command)
		return ;
	i = 0;
	new_cmd = NULL;
	while (cmd->command && cmd->command[i])
	{
		if (cmd->command[i] == '"' && cmd->command[i + 1] == cmd->command[i])
			i += 2;
		tmp_cmd = new_cmd;
		new_cmd = char_concat(new_cmd, cmd->command[i]);
		free(tmp_cmd);
		i++;
	}
	free(cmd->command);
	cmd->command = new_cmd;
}
