#include "../../../include/include.h"

t_token *token_line(char *line)
{
    t_token *tokens;
    tokens = NULL;
    while (*line)
    {
        while (*line && ft_strchr(" \t\n", *line))
            line++;
        if (ft_strchr("><|", *line))
        {
            do_speacil_chars(&line, &tokens);

        }
        else
        {
            //printf(" in befor in word %s\n", line);
            do_words(&line, &tokens);
            //printf("in after in word %s\n", line);
        }
    }
    return (tokens);
}
void    do_words(char **line, t_token **tokens)
{
    char *start;
    int in_qoute;
    char quote_char;

    start = *line;
    in_qoute = 0;
    quote_char = '\0';
    while (**line)
    {
        update_quote_status(**line ,&in_qoute, &quote_char);
        if (!in_qoute && ft_strchr(" \t\n><|", **line))
            break;
        (*line)++;
    }
    word_to_token(&start, line, tokens);
}

void    do_speacil_chars(char **line, t_token **tokens)
{
    if (**line == '>')
    {
        if (*(*line + 1) == '>')
        {
            add_token_to_list(tokens, new_token(TOKEN_REDIR_APPEND, ">>"));
            (*line)++;
        }
        else
            add_token_to_list(tokens, new_token(TOKEN_REDIR_OUT, ">"));
    }
    else if (**line == '<')
    {
        if (*(*line + 1) == '<')
        {
            add_token_to_list(tokens, new_token(TOKEN_REDIR_HEREDOC, "<<"));
            (*line)++;
        }
        else
            add_token_to_list(tokens, new_token(TOKEN_REDIR_IN, "<"));
    }
    else if (**line == '|')
        add_token_to_list(tokens, new_token(TOKEN_PIPE, "|"));
    (*line)++;
}