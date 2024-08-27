/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:29:04 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:17 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	ft_exit(char **arg)
{
	int	exit_status;

	if (NULL == arg)
		exit_status = 0;
	else if (split_len(arg) > 1)
		return (printf("exit\nexit: too many arguments\n"), set_exit_status(1));
	else if (str_isdigit(arg[0]) == 2)
		exit_status = 2;
	else
		exit_status = ft_atoi(arg[0]);
	free_split(arg);
	set_exit_status(exit_status);
	exit(exit_status);
}
