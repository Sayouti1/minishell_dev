#include "./../../../include/include.h"


static int check_value(char *str)
{
    int i = 0;
    char *file;

    file = ft_strtrim(str, " ");
    if (file == NULL || *file == '\0')
        return (1);
    while (str[i])
    {
        if (str[i] == ' ')
            return (1);
        i++;
    }
    return (0);
}

int ft_ambiguous_err(t_token *tokens)
{
    t_token *token;
    char *value;

    token = tokens;
    while (token)
    {
        if (token->type == 3 && token->next->type == 0)
        {
           value = substitute_var1(token->next->value);
           if (check_value(value))
                return (1); 
        }
        token = token->next;
    }
    return (0);
}

