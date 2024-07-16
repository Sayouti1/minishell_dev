/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:30:00 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:05 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by abdelaziz on 6/27/24.
//

#include "../../include/include.h"

char	*get_dollar_key(char *line, int *i)
{
	int		j;
	int		k;
	char	*key;

	j = *i + 1;
	while (line[j] && line[j] != ' ' && line[j] != '$' && line[j] != '\''
		&& line[j] != '"')
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

char	*get_var_dollar(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i] && line[i] != 32)
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (NULL == tmp)
		return (NULL);
	tmp[i--] = 0;
	while (i >= 0)
	{
		tmp[i] = line[i];
		--i;
	}
	return (tmp);
}
/*
 * ✅
 */
char	*get_correct_path(char **split, char *curr_dir)
{
	char	*full_path;

	if (NULL == split || NULL == split[0])
		return (NULL);
	if (split[0][0] == '.')
		full_path = ft_strjoin_prefixed(curr_dir, '/', split[0]);
	else if (split[0][0] == '/')
		full_path = ft_strdup(split[0]);
	else
		full_path = bin_in_path(split[0]);
	if (NULL == full_path)
		return (NULL);
	return (full_path);
}
/*
 * ✅
 */
char	**get_exec_arg(char *fullpath, char *split)
{
	char	**exec_arg;
	char	**arg;
	int		i;

	arg = ft_split_del(split, " \t");
	i = 0;
	while (arg && arg[i])
		i++;
	exec_arg = (char **)malloc(sizeof(char *) * (i + 2));
	if (NULL == exec_arg)
		return (set_exit_status(1), NULL);
	exec_arg[0] = ft_strdup(fullpath);
	i = 0;
	while (arg && arg[i])
	{
		exec_arg[i + 1] = arg[i];
		++i;
	}
	exec_arg[i + 1] = NULL;
	return (exec_arg);
}
