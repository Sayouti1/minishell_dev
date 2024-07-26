/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:30:28 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:31 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by abdelaziz on 6/23/24.
//

#include "../../../include/include.h"

/*
 * TRIM USER INPUT IN A NEW ALLOCATED STRING,
 * AND RETURN IT , THEN FREE THE OLD READLINE
 */
char	*trim_and_free(char *line)
{
	char	*trimmed;

	if (NULL == line)
		return (NULL);
	if (line[0] == '\0')
		return (line);
	trimmed = ft_strtrim(line, " 	");
	if (NULL == trimmed)
		return (NULL);
	free(line);
	return (trimmed);
}

char	*char_concat(char *line, char c)
{
	char	*concat;
	int		i;
	int		j;

	i = ft_strlen(line);
	concat = (char *)malloc(sizeof(char) * (i + 2));
	if (NULL == concat)
		return (NULL);
	j = 0;
	i = 0;
	while (line && line[i])
		concat[j++] = line[i++];
	concat[j++] = c;
	concat[j] = '\0';
	//free(line);
	return (concat);
}

char	*string_concat(char *line, char *str)
{
	int		i;
	int		j;
	char	*concat;

	i = ft_strlen(str) + ft_strlen(line);
	concat = (char *)malloc(sizeof(char) * (i + 1));
	if (NULL == concat)
		return (NULL);
	i = 0;
	j = 0;
	while (line && line[i])
		concat[j++] = line[i++];
	i = 0;
	while (str && str[i])
		concat[j++] = str[i++];
	concat[j] = '\0';
	free(line);
	free(str);
	return (concat);
}

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
