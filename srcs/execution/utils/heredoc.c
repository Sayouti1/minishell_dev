/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:16:16 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

char	*substitute_var(char *str)
{
	int		i;
	char	*concat;
	char	*key;

	if (NULL == str)
		return (NULL);
	concat = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			concat = char_concat(concat, str[i++]);
		if (str[i] == '$' && str[i + 1] == '?' && ++i && ++i)
			concat = string_concat(concat, ft_itoa(g_vars.exit_status));
		if (str[i] == '$')
		{
			if (str[i + 1] == '{')
				++i;
			key = get_dollar_key_v1(str, &i);
			while (str[i] && ft_char_in(str[i], " \t}"))
				++i;
			concat = string_concat(concat, ft_strdup(get_env_v1(key)));
			free(key);
		}
	}
	return (concat);
}

int	check_curly_braces(char *str)
{
	int	i;

	if (NULL == str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (!str[i + 1] || ft_isspace(str[i + 1])) && ++i)
			continue ;
		if (str[i] == '$' && str[i + 1] == '{')
		{
			i += 2;
			while (str[i] && !ft_char_in(str[i], " \n{}"))
				++i;
			if (str[i] != '}')
				return (1);
		}
		++i;
	}
	return (0);
}

int	open_heredoc(t_redirection *redirection)
{
	char	buff[1000];
	size_t	byte_read;
	char	*del;
	int		fds[2];

	del = char_concat(redirection->file_name, '\n');
	//free(cmd->redirection->file_name)
	redirection->file_name = NULL;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		byte_read = read(0, buff, 1000);
		buff[byte_read] = '\0';
		if (byte_read <= 0 || !ft_strncmp(buff, del, ft_strlen(del)))
			break ;
		redirection->file_name = ft_strjoin_gnl(redirection->file_name, buff);
	}
	pipe(fds);
	if (!ft_char_in('\'', del) && !ft_char_in('"', del))
	{
		if (check_curly_braces(redirection->file_name))
		{
			set_exit_status(1);
			return (printf(" : bad substitution\n"), 1);
		}
		redirection->file_name = substitute_var(redirection->file_name);
	}
	write(fds[1], redirection->file_name, ft_strlen(redirection->file_name));
	close(fds[1]);
	redirection->fd = fds[0];
	return (dup2(redirection->fd, 0), 0);
}
