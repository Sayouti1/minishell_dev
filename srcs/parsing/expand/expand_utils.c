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
	file = ft_strtrim(str, " ");
	if (file == NULL || *file == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			return (1);
			free(file);
		}
		i++;
	}
	free(file);
	return (0);
}

int	ft_ambiguous_err(t_token *tokens)
{
	t_token	*token;
	char	*value;

	token = tokens;
	while (token)
	{
		if ((token->type == 3 || token->type == 2 || token->type == 4)
			&& token->next->type == 0)
		{
			value = substitute_var1(token->next->value);
			if (check_value(value))
				return (1);
		}
		token = token->next;
	}
	return (0);
}
