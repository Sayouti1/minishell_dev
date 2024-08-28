#include "../../../include/include.h"

char    *substitute_var1(char *str)
{
    int     i;
    char    *concat;
    char    *key;
    int     in_quotes;

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
            continue;
        }
        if (str[i] == '$' && str[i + 1] == '?' && ++i && ++i)
            concat = string_concat(concat, ft_itoa(g_vars.exit_status));
        else if (str[i] == '$' && (in_quotes || (str[i + 1] != '\'' && str[i + 1] != ' ')))
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

void expand_var(t_token **tokens) 
{
    t_token *token; 
	token = *tokens;
    char **words;

    while (token) {
        if (token->type == TOKEN_WORD) {
            //char *expanded = parse_command_vars(token->value);
            char *expanded = substitute_var1(token->value);
            
            if (expanded != NULL) {
                //free(token->value);
 				//printf("expand word from expanded %s\n\n",expanded);
                token->value = expanded;
                words = ft_split(token->value, ' ');
                int i = 0;
                while (words[i])
                {
                    printf("%s\n",words[i]);
                    i++;
                }
            }
 		//printf("expand word %s\n\n",token->value);
        }
        token = token->next;
    }
}