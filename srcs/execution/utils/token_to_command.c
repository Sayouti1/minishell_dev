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

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (NULL == new_ptr)
		return (NULL);
	ft_memset(new_ptr, 0, size);
	if (ptr)
	{
		ft_memmove(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

char	**add_to_list(char **old_list, char *to_add)
{
	int		i;
	char	**new_list;

	i = split_len(old_list);
	new_list = ft_realloc(old_list, (i + 2) * sizeof(char *));
	if (NULL == new_list)
		return (printf("ERROR allocating new_list\n"), NULL);
	new_list[i] = to_add;
	new_list[++i] = NULL;
	return (new_list);
}

int	has_null(t_redirection *red)
{
	t_redirection	*tmp;

	tmp = red;
	while (tmp)
	{
		if (tmp->type != HEREDOC && NULL == tmp->file_name)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_redirection	*add_redirection(t_redirection *red, t_token **token)
{
	int				red_type;
	t_redirection	*new_red;
	t_token			*tmp;

	red_type = token_type_to_cmd_type((*token)->type);
	tmp = *token;
	(*token) = (*token)->next;
	if (NULL == *token)
		return (red);
	if ((*token)->type != TOKEN_WORD)
	{
		new_red = new_redirection(red_type, NULL, -1, !has_null(red));
		(*token) = tmp;
	}
	else
		new_red = new_redirection(red_type, (*token)->value, -1, !has_null(red));
	if (NULL == red)
		red = new_red;
	else
		get_last_red(red)->next = new_red;
	return (red);
}

void	copy_cmd_args(t_token **token, t_command **cmd)
{
	char	**args;

	args = NULL;
	free_split((*cmd)->args);
	if (*token && (*token)->type == TOKEN_WORD)
	{
		(*cmd)->command = (*token)->value;
		*token = (*token)->next;
	}
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		while ((*token) && (*token)->type == TOKEN_WORD)
		{
			args = add_to_list(args, (*token)->value);
			(*token) = (*token)->next;
		}
		while ((*token) && (*token)->type != TOKEN_PIPE && (*token)->type != TOKEN_WORD)
		{
			(*cmd)->redirection = add_redirection((*cmd)->redirection, token);
			(*token) = (*token)->next;
		}
		// if (*token)
		// 	*token = (*token)->next;
	}
	(*cmd)->args = args;
}

int	token_to_command_convert(t_token *token, t_command **cmd)
{
	t_token		*tmp_token;
	t_command	*tmp_cmd;

	tmp_token = token;
	while (tmp_token)
	{
		tmp_cmd = new_command(NULL, NULL, NULL);
		copy_cmd_args(&tmp_token, &tmp_cmd);
		remove_quotes(tmp_cmd);
		add_to_cmds(cmd, tmp_cmd);
		if (tmp_token)
			tmp_token = tmp_token->next;
	}
	return (0);
}
