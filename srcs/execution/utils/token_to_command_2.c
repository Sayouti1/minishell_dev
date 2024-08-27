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

char	*trim_str(char *str)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			++i;
			while (str[i] && str[i] != '\'')
				tmp = char_concat(tmp, str[i++]);
		}
		else if (str[i] == '"')
		{
			++i;
			while (str[i] && str[i] != '"')
				tmp = char_concat(tmp, str[i++]);
		}
		else
			tmp = char_concat(tmp, str[i]);
		collect_garbage(tmp);
	}
	free(str);
	return (tmp);
}

void	remove_quotes(t_command *cmd)
{
	int	i;

	if (NULL == cmd)
		return ;
	if (cmd->command)
		cmd->command = trim_str(ft_strdup(cmd->command));
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		cmd->args[i] = trim_str(ft_strdup(cmd->args[i]));
		++i;
	}
}

int	token_type_to_cmd_type(t_token_type type)
{
	if (TOKEN_REDIR_IN == type)
		return (INPUT);
	if (TOKEN_REDIR_OUT == type)
		return (OUTPUT);
	if (TOKEN_REDIR_APPEND == type)
		return (APPEND);
	if (TOKEN_REDIR_HEREDOC == type)
		return (HEREDOC);
	else
		return (printf("error token_type to cmd_type\n"), 99);
}
