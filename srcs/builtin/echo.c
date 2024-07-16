/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:48 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:28:51 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by abdelaziz on 6/27/24.
//
#include "../../include/include.h"

/*
 * ECHO FUNCTION ✅
 */
void	ft_echo(char *str)
{
	int		n_flag;
	char	**split;
	int		i;

	split = ft_split_del(str, " \t");
	if (NULL == split)
		return ;
	n_flag = 0;
	if (!ft_strcmp(split[0], "-n"))
		n_flag = 1;
	i = n_flag;
	while (split[i])
	{
		printf("%s", split[i]);
		if (split[i + 1])
			printf(" ");
		++i;
	}
	if (!n_flag)
		printf("\n");
	free_split(split);
}
