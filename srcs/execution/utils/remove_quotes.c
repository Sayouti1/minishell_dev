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
/*
 * remove_edge_quotes : // Removes any pairs of single ('') or double quotes (""")
 * from the beginning and end of command and its args.
*/
int	remove_edge_quotes(t_command *cmd)
{
	char		*tmp;
	int			start;
	int			end;
	int			i;

	tmp = cmd->command;
	get_start_end(cmd->command, &start, &end);
	if (start > end || NULL == cmd->command)
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

char	*remove_double_quotes_middle(char *str)
{
	char 	*new_str;
	char 	*tmp;
	int		i;

	if (NULL == str)
		return (NULL);
	i = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '"' && str[i + 1] == str[i])
			i += 2;
		tmp = new_str;
		new_str = char_concat(new_str, str[i]);
		free(tmp);
		i++;
	}
	free(str);
	return (new_str);
}

char	*remove_all_quotes(char *str)
{
	char 	*trimmed;
	int		i;
	int		j;

	if (NULL == str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != '\'' && str[i] != '"')
			++j;
	trimmed = malloc(sizeof(char) * (j + 1));
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != '\'' && str[i] != '"')
			trimmed[j++] = str[i];
	trimmed[j] = '\0';
	// free(str);
	return (trimmed);
}
