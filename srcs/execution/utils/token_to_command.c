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
	// new_list = (char **)malloc(sizeof(char *) * (i + 2));
	if (NULL == new_list)
		return (printf("ERROR allocating new_list\n"), NULL);
	// i = 0;
	// // collect_garbage(new_list);
	// while (old_list && old_list[i])
	// {
	// 	new_list[i] = ft_strdup(old_list[i]);
	// 	if (new_list[i] == NULL)
	// 		return (printf("ERROR allocating new_list[i]\n"),
	// 			NULL);
	// 			// free_split(new_list),
	// 	// collect_garbage(new_list[i]);
	// 	++i;
	// }
	new_list[i] = to_add;
	// // collect_garbage(to_add);
	new_list[++i] = NULL;
	// free_split(old_list);
	return (new_list);
}
char **list;
t_redirection	*get_last_red(t_redirection *red)
{
	while (red && red->next)
		red = red->next;
	return (red);
}

t_redirection	*add_redirection(t_redirection *red, t_token **token)
{
	int				red_type;
	t_redirection	*new_red;

	red_type = token_type_to_cmd_type((*token)->type);
	(*token) = (*token)->next;
	new_red = new_redirection(red_type, (*token)->value, -1);
	// collect_garbage(new_red);
	if (NULL == red)
		red = new_red;
	else
		get_last_red(red)->next = new_red;
	return (red);
}

void	copy_cmd_args(t_token **token, t_command **cmd)
{
	char			**args;
	// t_redirection	*red;

	args = NULL;
	// red = NULL;
	free_split((*cmd)->args);
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
			(*cmd)->redirection = add_redirection((*cmd)->redirection, token);
		*token = (*token)->next;
	}
	(*cmd)->args = args;
	// (*cmd)->redirection = red;
}

int			expand_vars(t_command *tmp_cmd)
{
	char 	*tmp;
	int		i;

	if (ft_char_in('$', tmp_cmd->command))
		return (0);
	tmp = tmp_cmd->command;
	tmp_cmd->command = substitute_var(tmp_cmd->command);
	free(tmp);
	i = 0;
	while (tmp_cmd && tmp_cmd->args && tmp_cmd->args[i])
	{
		tmp = tmp_cmd->args[i];
		tmp_cmd->args[i] = substitute_var(tmp_cmd->args[i]);
		free(tmp);
		++i;
	}
	return (0);
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
		remove_edge_quotes(tmp_cmd);
		remove_double_quotes(tmp_cmd);
		remove_double_quotes_middle(tmp_cmd);
		// expand_vars(tmp_cmd);
		add_to_cmds(cmd, tmp_cmd);
		if (tmp_token)
			tmp_token = tmp_token->next;
	}
	return (0);
}
