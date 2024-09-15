/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:38:36 by aez-zoui          #+#    #+#             */
/*   Updated: 2024/09/05 22:38:39 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../include/include.h"

static int	check_value(char *str)
{
	int		i;
	char	*file;

	i = 0;
	file = ft_strtrim(str, " \t\n\v");
	if (file == NULL || *file == '\0')
		return (free(file), 1);
	while (file[i])
	{
		if (is_trim(file[i]))
			return (free(file), 1);
		i++;
	}
	return (free(file), 0);
}

int	ft_ambiguous_err(t_token *tokens)
{
	t_token	*token;
	char	*value;

	token = tokens;
	while (token)
	{
		if ((token->type == 3 || token->type == 2 || token->type == 4)
			&& token->next->type == 0 && ft_strchr(token->next->value, '$'))
		{
			value = substitute_var1(token->next->value);
			if (check_value(value))
				return (free(value), 1);
			free(value);
		}
		token = token->next;
	}
	return (0);
}

char	*surround_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc((ft_strlen(str) + 3) * sizeof(char));
	if (NULL == new_str)
		return (free(str), NULL);
	new_str[0] = '"';
	j = 1;
	i = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j++] = '"';
	new_str[j++] = '\0';
	free(str);
	return (new_str);
}

