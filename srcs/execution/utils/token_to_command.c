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

void    copy_cmd_args(t_token **token, t_command **cmd)
{
    if (*token && (*token)->type == TOKEN_WORD)
    {
        (*cmd)->command = (*token)->value;
        *token = (*token)->next;
    }
    while (*token && (*token)->value != TOKEN_PIPE)
    {
        
        *token = (*token)->next;
    }
}
/*
 *
 *TO BE FIXED TOMORROW
 * 
*/
int token_to_command_convert(t_token *token, t_command **cmd)
{
    t_token *tmp_token;
    t_command   *tmp_cmd;

    tmp_token = token;
    (void)cmd;
    while (tmp_token)
    {
        tmp_cmd = new_command(NULL, NULL, NULL);
        copy_cmd_args(&tmp_token, &tmp_cmd);
        tmp_token = tmp_token->next;
    }
    return (0);
}