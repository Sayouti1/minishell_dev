/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:30:00 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

/*
 * ✅
 */
char	*get_correct_path(char *split, char *curr_dir)
{
	char	*full_path;

	if (NULL == split)
		return (NULL);
	if (split[0] == '.')
		full_path = ft_strjoin_prefixed(curr_dir, '/', split);
	else if (split[0] == '/')
		full_path = ft_strdup(split);
	else
		full_path = bin_in_path(split);
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
