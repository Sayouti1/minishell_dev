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

static char	*handle_single_quotes(char *str, int *i, char *concat)
{
	concat = char_concat(concat, str[(*i)++]);
	while (str[*i] && str[*i] != '\'')
		concat = char_concat(concat, str[(*i)++]);
	if (str[*i])
		concat = char_concat(concat, str[(*i)++]);
	return (concat);
}

char	*substitute_var1(char *str)
{
	int		i;
	char	*concat;
	int		in_quotes;

	concat = NULL;
	i = 0;
	in_quotes = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			in_quotes = !in_quotes;
		if (str[i] == '\'' && !in_quotes)
			concat = handle_single_quotes(str, &i, concat);
		else if (str[i] == '$')
			concat = handle_dollar_sign(str, &i, concat, in_quotes);
		else
			concat = char_concat(concat, str[i++]);
	}
	return (concat);
}

static void	handle_heredoc(t_token **ntoken, t_token **token)
{
	add_token_to_list(ntoken, new_token((*token)->type, (*token)->value));
	*token = (*token)->next;
	if (*token && (*token)->type == TOKEN_WORD)
		add_token_to_list(ntoken, new_token((*token)->type, (*token)->value));
}

static void	handle_word_expansion(t_token **ntoken, t_token **token)
{
	char	*expand;
	char	**words;
	int		i;

	expand = substitute_var1((*token)->value);
	if (expand[0] == '"' || expand[0] == 'l')
		add_token_to_list(ntoken, new_token((*token)->type, expand));
	else
	{
		words = ft_split(expand, ' ');
		i = -1;
		while (words && words[++i])
			add_token_to_list(ntoken, new_token(TOKEN_WORD, words[i]));
		free_words(words);
	}
	free(expand);
}

t_token	*expand_var(t_token *tokens)
{
	t_token	*token;
	t_token	*ntoken;

	ntoken = NULL;
	token = tokens;
	while (token)
	{
		if (token->type == TOKEN_REDIR_HEREDOC)
			handle_heredoc(&ntoken, &token);
		else if (token->type == TOKEN_WORD && ft_strchr(token->value, '$'))
			handle_word_expansion(&ntoken, &token);
		else
			add_token_to_list(&ntoken, new_token(token->type, token->value));
		token = token->next;
	}
	return (ntoken);
}
