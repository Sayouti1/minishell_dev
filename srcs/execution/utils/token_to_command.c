/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:33:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/14 20:34:53 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

char **add_to_list(char **list, char *str)
{
    int     i;
    char    **new_list;

    i = split_len(list);
    new_list = (char **)malloc(sizeof(char *) * (i + 2));
    if (NULL == new_list)
        return (printf("ERROR allocating new_list\n"), NULL);
    i = 0;
    while (list && list[i])
    {
        new_list[i] = ft_strdup(list[i]);
        if (new_list[i] == NULL)
            return (printf("ERROR allocating new_list[i]\n"), free_split(new_list), NULL);
        ++i;
    }
    new_list[i++] = ft_strdup(str);
    new_list[i] = NULL;
    free_split(list);
    return (new_list);
}

int token_type_to_cmd_type(t_token_type type)
{
    if (TOKEN_REDIR_IN == type)
    {
        return (INPUT);
	}
    if (TOKEN_REDIR_OUT == type)
    {
        return (OUTPUT);
	}
    if (TOKEN_REDIR_APPEND == type)
     
    {   return (APPEND);
	}
    if (TOKEN_REDIR_HEREDOC == type)
    {
        return (HEREDOC);
    }
    else
        return (printf("error token_type to cmd_type\n"), 99);
}

t_redirection   *get_last_red(t_redirection *red)
{
    while (red && red->next)
        red = red->next;
    return (red);
}

t_redirection   *add_redirection(t_redirection *red, t_token **token)
{
    int red_type;

    red_type = token_type_to_cmd_type((*token)->type);
    (*token) = (*token)->next;
    if (NULL == red)
        red = new_redirection(red_type, ft_strdup((*token)->value), -1);
    else
        get_last_red(red)->next = new_redirection(red_type, ft_strdup((*token)->value), -1);
    return (red);
}

void    copy_cmd_args(t_token **token, t_command **cmd)
{
    char            **args;
    t_redirection   *red;

    args = NULL;
    red = NULL;
    if (*token && (*token)->type == TOKEN_WORD)
    {
        (*cmd)->command = ft_strdup((*token)->value);
        *token = (*token)->next;
    }
    while (*token && (*token)->type != TOKEN_PIPE)
    {
        if ((*token)->type == TOKEN_WORD)
            args = add_to_list(args, (*token)->value);
        else if ((*token)->type != TOKEN_PIPE && (*token)->type != TOKEN_WORD)
            red = add_redirection(red, token);
        *token = (*token)->next;
    }
    (*cmd)->args = args;
    (*cmd)->redirection = red;   
}

int token_to_command_convert(t_token *token, t_command **cmd)
{
    t_token     *tmp_token;
    t_command   *tmp_cmd;

    tmp_token = token;
    while (tmp_token)
    {
        tmp_cmd = new_command(NULL, NULL, NULL);
        copy_cmd_args(&tmp_token, &tmp_cmd);
        add_to_cmds(cmd, tmp_cmd);
        if (tmp_token)
            tmp_token = tmp_token->next;
    }
    return (0);
}