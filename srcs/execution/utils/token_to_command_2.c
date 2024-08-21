/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:33:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/14 20:34:53 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	trim_cmd(t_command *cmd)
{
	char	*tmp;

	if (NULL == cmd || NULL == cmd->command)
		return ;
	tmp = NULL;
	if (cmd->command[0] == '"')
		tmp = ft_strtrim(cmd->command, "\"");
	else
		tmp = ft_strtrim(cmd->command, "'");
	free(cmd->command);
	cmd->command = tmp;
}

void	trim_args(t_command *cmd, int i)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->args[i][0] == '\'')
		tmp = ft_strtrim(cmd->args[i], "'");
	else
		tmp = ft_strtrim(cmd->args[i], "\"");
	free(cmd->args[i]);
	cmd->args[i] = tmp;
}

//WORKING ON THIS :red_circle:
void	remove_double_quotes(t_command *cmd)
{
	int	i;

	if (cmd->command && (cmd->command[0] == '\'' || cmd->command[0] == '"'))
		trim_cmd(cmd);
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		if ((cmd->args[i][0] == '\'' && cmd->args[i][ft_strlen(cmd->args[i])
			- 1] == '\'') ||
			(cmd->args[i][0] == '"' && cmd->args[i][ft_strlen(cmd->args[i])
			- 1] == '"'))
			trim_args(cmd, i);
	}
}

int	token_type_to_cmd_type(t_token_type type)
{
	if (TOKEN_REDIR_IN == type)
	{
		return (INPUT);
	}
	if (TOKEN_REDIR_OUT == type)
	{
		return (OUTPUT);
	}
	if (TOKEN_REDIR_APPEND == type)
	{
		return (APPEND);
	}
	if (TOKEN_REDIR_HEREDOC == type)
	{
		return (HEREDOC);
	}
	else
		return (printf("error token_type to cmd_type\n"), 99);
}
