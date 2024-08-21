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
#include "../../../include/include.h"

/*
 * ECHO FUNCTION ✅
 */

int	n_option(int *i, char **str)
{
	int	j;
	int	n_flag;

	n_flag = 0;
	while (str[*i] && str[*i][0] == '-')
	{
		j = 1;
		while (str[*i][j] && ft_char_in(str[*i][j], "en"))
			j++;
		if (str[*i][j])
		{
			if (*i > 0)
				--(*i);
			break ;
		}
		if (ft_char_in('n', str[*i]))
			n_flag = 1;
		++(*i);
	}
	return (n_flag);
}

void	ft_echo(char **str)
{
	int	n_flag;
	int	i;

	i = 0;
	n_flag = n_option(&i, str);
	while (str[i])
	{
		printf("%s", str[i++]);
		if (str[i] && str[i][0])
			printf(" ");
	}
	if (n_flag == 0)
		printf("\n");
}
