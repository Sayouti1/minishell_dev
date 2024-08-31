/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:31:00 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:19:53 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	ft_isspace(char c)
{
	return ((c >= 7 && c <= 13) || c == 32);
}

int	str_isdigit(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (NULL == str)
		return (0);
	while (ft_char_in(str[i], " \t"))
		++i;
	j = ft_strlen(str) - 1;
	while (j >= 0 && ft_char_in(str[j], " \t"))
		--j;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i] && i <= j)
		if (!ft_isdigit(str[i++]))
			return (printf("exit: %s : numeric argument required\n", str), 2);
	return (1);
}
