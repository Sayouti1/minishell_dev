/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:37 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:39 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by abdelaziz on 6/8/24.
//

#include "../../../include/include.h"

int	ft_export(char **var)
{
	char	**key_value;
	char	**split;
	int		i;

	split = ft_split_del(var[0], " \t");
	if (NULL == split)
		return (set_exit_status(1), 1);
	i = 0;
	while (split[i])
	{
		key_value = split_on_two(split[i++], "=");
		if (NULL == key_value || NULL == key_value[1])
			return (set_exit_status(0), 1);
		printf("split[%d] => [%s], [%s=>%s]\n", i - 1, split[i - 1],
				key_value[0], key_value[1]);
		if (!ft_env_replace(key_value[0], key_value[1]))
			add_to_env(ft_strdup(key_value[0]), ft_strdup(key_value[1]));
		free_split(key_value);
	}
	free_split(split);
	return (set_exit_status(0), 0);
}

void	ft_print_export(void)
{
	while (g_vars.env)
	{
		printf("export %s=%s\n", g_vars.env->key, g_vars.env->value);
		g_vars.env = g_vars.env->next;
	}
	set_exit_status(0);
}
