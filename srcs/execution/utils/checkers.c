/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:42 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:28:44 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by helloworld on 6/13/24.
//

#include "../../../include/include.h"

/*
 * CHECK FOR SINGLE AND DOUBLE QUOTES NUMBER
 */
int	closed_quotes(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	if (NULL == str)
		return (1);
	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			s_quote++;
		if (str[i] == '"')
			d_quote++;
		i++;
	}
	return (s_quote % 2 == 0 && d_quote % 2 == 0);
}

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
