/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:30:28 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by abdelaziz on 6/23/24.
//

#include "../../../include/include.h"

/*
 * PARSE THE USER INPUT AND REPLACE
 * DOLLAR AND ENVIRONMENT VARIABLES
 *
 * NEEDS SOME IMPROVEMENT (NORMINETTE ETC...)
 */
char	*parse_command_vars(char *line)
{
	int		sq_open;
	int		dq_open;
	char	*concat;
	int		i;
	char	*key;

	sq_open = 0;
	dq_open = 0;
	i = 0;
	concat = NULL;
	while (line && line[i])
	{
		if (line[i] == '\'' && !dq_open && ++i)
			sq_open = !sq_open;
		else if (line[i] == '"' && ++i)
			dq_open = !dq_open;
		if (sq_open && !dq_open)
		{
			while (line[i] && line[i] != '\'')
				concat = char_concat(concat, line[i++]);
			if (line[i] == '\'' && ++i)
				sq_open = !sq_open;
			continue ;
		}
		if (line[i] == '$' && line[i + 1] == '?')
		{
			concat = string_concat(concat, ft_itoa(g_vars.exit_status));
			i += 2;
		}
		if (line[i] == '$')
		{
			key = get_dollar_key(line, &i);
			concat = string_concat(concat,
									ft_strdup(get_env_v1(key)));
			free(key);
			continue ;
		}
		if (line[i])
			if (!(line[i] == '"' && dq_open))
				concat = char_concat(concat, line[i++]);
	}
	free(line);
	return (concat);
}
