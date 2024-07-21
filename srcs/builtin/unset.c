/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:30:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:53 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by abdelaziz on 6/8/24.
//

#include "../../include/include.h"

int	ft_unset(char **key)
{
	t_env	*iter;
	t_env	*tmp;
	char	**split;
	int		i;

	split = ft_split_del(key[0], " \t");
	if (NULL == split)
		return (1);
	iter = g_vars.env;
	i = -1;
	while (split[++i])
	{
		if (iter && !ft_strcmp(iter->key, split[i]))
		{
			g_vars.env = iter->next;
			delete_env(iter);
		}
		else
		{
			while (iter)
			{
				if (iter->next && !ft_strcmp(iter->next->key, split[i]))
					break ;
				iter = iter->next;
			}
		}
		if (NULL == iter)
			return (set_exit_status(0));
		tmp = iter->next;
		iter->next = iter->next->next;
		delete_env(tmp);
	}
	return (set_exit_status(0));
}
