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

	concat = NULL;
	i = 0;
	while (str && str[i])
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
		return (0);
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

int	read_and_join(char *buff, char *del, t_redirection *redirection)
{
	size_t	byte_read;

	byte_read = read(0, buff, 1000);
	buff[byte_read] = '\0';
	if (byte_read <= 0 || !ft_strncmp(buff, del, ft_strlen(del)))
		return (1);
	redirection->file_name = ft_strjoin_gnl(redirection->file_name, buff);
	return (0);
}

int	open_heredoc(t_redirection *redirection)
{
	char	buff[1000];
	char	*del;
	int		fds[2];

	del = char_concat(redirection->file_name, '\n');
	redirection->file_name = NULL;
	signal(SIGQUIT, ignore_sig);
	while (1)
		if (read_and_join(buff, del, redirection))
			break ;
	pipe(fds);
	if (!ft_char_in('\'', del) && !ft_char_in('"', del))
	{
		if (check_curly_braces(redirection->file_name))
			return (set_exit_status(1), printf(" : bad substitution\n"), 1);
		redirection->file_name = substitute_var(redirection->file_name);
	}
	write(fds[1], redirection->file_name, ft_strlen(redirection->file_name));
	close(fds[1]);
	redirection->fd = fds[0];
	return (dup2(redirection->fd, 0), 0);
}

// int	open_heredoc(t_redirection *redirection)
// {
// 	char	*line;
// 	char	*del;
// 	int		fds[2];
// 	char	*text;
// 	// int		sub_var;

// 	// sub_var = 0;
// 	// if (!ft_char_in('\'', redirection->file_name)
// 		// && !ft_char_in('"', redirection->file_name))
// 		// sub_var = 1;
// 	del = remove_all_quotes(redirection->file_name);
// 	redirection->file_name = NULL;
// 	signal(SIGQUIT, ignore_sig);
// 	pipe(fds);
// 	text = NULL;
// 	while (1)
// 	{
// 		line = readline(">");
// 		if (NULL == line)
// 			break ;
// 		if (!ft_strcmp(line, del))
// 		{
// 			free(line);
// 			break;
// 		}
// 		text = ft_strjoin_gnl(text,);
// 		// if (check_curly_braces(line))
// 		// 	return (set_exit_status(1), printf(" : bad substitution\n"), 1);
// 		ft_putstr_fd(line, fds[1]);
// 		ft_putchar_fd('\n', fds[1]);
// 		free(line);
// 	}
// 	free(del);
// 	// if (!ft_char_in('\'', del) && !ft_char_in('"', del))
// 	// {
// 	// 	if (check_curly_braces(redirection->file_name))
// 	// 		return (set_exit_status(1), printf(" : bad substitution\n"), 1);
// 	// 	redirection->file_name = substitute_var(redirection->file_name);
// 	// }
// 	// write(fds[1], redirection->file_name, ft_strlen(redirection->file_name));
// 	close(fds[1]);
// 	redirection->fd = fds[0];
// 	return (dup2(redirection->fd, 0), 0);
// }
