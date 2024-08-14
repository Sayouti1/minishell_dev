#include "../../include/include.h"

int closed_quotes(char *str)
{
    int d_count = 0;
    int s_count = 0;
    int i = 0;
    char current_quote = '\0';

    while (str[i])
    {
        if (current_quote == '\0')
        {
            if (str[i] == '"')
            {
                current_quote = '"';
                d_count++;
            }
            else if (str[i] == '\'')
            {
                current_quote = '\'';
                s_count++;
            }
        }
        else if (str[i] == current_quote)
        {
            if (current_quote == '"')
                d_count++;
            else
                s_count++;
            current_quote = '\0';
        }
        i++;
    }
    return (s_count % 2 == 0 && d_count % 2 == 0);
}