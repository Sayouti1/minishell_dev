#include "./../../../include/include.h"

void update_quote_status(char c, int *is_quote, char *qoute_char)
{
    if (!*is_quote && (c == '\'' || c == '\"'))
    {
        *is_quote = 1;
        *qoute_char = c;
    }
    else if (*is_quote && c == *qoute_char)
        *is_quote = 0;
}

t_token *new_token(t_token_type type, char *value)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = ft_strdup(value);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
    token->next = NULL;
    return (token);    
}

void    add_token_to_list(t_token **tokens, t_token *new_token)
{
    t_token *last;
    if(!*tokens)
        *tokens = new_token;
    else
    {
        last = *tokens;
        while (last->next)
            last = last->next;
        last->next = new_token;
    }
}

void free_token(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}

void word_to_token(char **start, char **line, t_token **tokens)
{
    char *word;
    if (*line > *start)
    {
        word = ft_strndup(*start, *line - *start);
        if (word)
        {
            add_token_to_list(tokens, new_token(TOKEN_WORD, word));
            free(word);
        }
        else
            ft_putstr_fd("Error malloc", 2);
    }
}
char	*ft_strndup(char *src, size_t n)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = 0;
	size = ft_strnlen(src, n);
	str = malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len])
		len++;
	return (len);
}