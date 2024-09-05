/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:38:03 by aez-zoui          #+#    #+#             */
/*   Updated: 2024/09/05 22:38:05 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

char	*substitute_var1(char *str)
{
	int		i;
	char	*concat;
	char	*key;
	int		in_quotes;

	concat = NULL;
	i = 0;
	in_quotes = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			in_quotes = !in_quotes;
		if (str[i] == '\'' && !in_quotes)
		{
			concat = char_concat(concat, str[i++]);
			while (str[i] && str[i] != '\'')
				concat = char_concat(concat, str[i++]);
			if (str[i])
				concat = char_concat(concat, str[i++]);
			continue ;
		}
		if (str[i] == '$' && str[i + 1] == '?' && ++i && ++i)
			concat = string_concat(concat, ft_itoa(g_vars.exit_status));
		else if (str[i] == '$' && ft_isalnum(str[i + 1]) && (in_quotes || (str[i
					+ 1] != '\'' && str[i + 1] != ' ')))
		{
			if (str[i + 1] == '{')
				++i;
			key = get_dollar_key_v1(str, &i);
			while (str[i] && ft_char_in(str[i], " \t}"))
				++i;
			concat = string_concat(concat, ft_strdup(get_env_v1(key)));
			free(key);
		}
		else
			concat = char_concat(concat, str[i++]);
	}
	return (concat);
}

t_token	*expand_var(t_token *tokens)
{
	t_token	*token;
	char	*expand;
	t_token	*ntoken;
	char	**words;
	int		i;

	ntoken = NULL;
	token = tokens;
	while (token)
	{
		if (token->type == TOKEN_REDIR_HEREDOC)
		{
			add_token_to_list(&ntoken, new_token(token->type, token->value));
			token = token->next;
			if (token && token->type == TOKEN_WORD)
				add_token_to_list(&ntoken, new_token(token->type,
						token->value));
		}
		else if (token->type == TOKEN_WORD && ft_strchr(token->value, '$'))
		{
			expand = substitute_var1(token->value);
			if (expand[0] == '"')
			{
				add_token_to_list(&ntoken, new_token(token->type, expand));
				printf("is not be split it\n\n\n");
				token = token->next;
				continue ;
			}
			printf("\n\nthis is expand value :%s\n\n", expand);
			words = ft_split(expand, ' ');
			i = 0;
			while (words && words[i])
				add_token_to_list(&ntoken, new_token(TOKEN_WORD, words[i++]));
		}
		else
			add_token_to_list(&ntoken, new_token(token->type, token->value));
		token = token->next;
	}
	return (ntoken);
}
