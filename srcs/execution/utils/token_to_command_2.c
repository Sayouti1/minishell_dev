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

	if (NULL == str)
		return (NULL);
	tmp = NULL;
	if (str[0] == '\'')
		tmp = ft_strtrim(str, "'");
	else
		tmp = ft_strtrim(str, "\"");
	free(str);
	return (tmp);
}

/* remove_double_quotes :  if the command or the args ! starts and end ! by a (') or (")
 * we trim the command and args by either ('') or ("") from both start and the end 
 *
*/
void	remove_double_quotes(t_command *cmd)
{
	int	i;

	if (NULL == cmd)
		return ;
	if (cmd->command && (cmd->command[0] == '\'' || cmd->command[0] == '"'))
	{
		cmd->command = trim_str(cmd->command);
		if (cmd->command && cmd->command[0] != '\'')
			cmd->command = remove_double_quotes_middle(cmd->command);
	}
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		if ((cmd->args[i][0] == '\'' && cmd->args[i][ft_strlen(cmd->args[i])
			- 1] == '\'') ||
			(cmd->args[i][0] == '"' && cmd->args[i][ft_strlen(cmd->args[i])
			- 1] == '"'))
			cmd->args[i] = trim_str(cmd->args[i]);
		if (cmd->args && cmd->args[i][0] != '\'')
			cmd->args[i] = remove_double_quotes_middle(cmd->args[i]);
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
