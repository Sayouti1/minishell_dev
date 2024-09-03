/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:42 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:12:52 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	built_in(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "clear_history"))
		return (1);
	return (0);
}

int	check_redirection(t_command *cmd)
{
	t_redirection	*red;

	if (NULL == cmd)
		return (0);
	red = cmd->redirection;
	while (red)
	{
		if (NULL == red->file_name)
			return (1);
		red = red->next;
	}
	return (0);
}
