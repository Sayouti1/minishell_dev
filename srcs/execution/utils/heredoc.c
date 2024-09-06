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

char	*expand_heredoc(char *line, int *bad_sub)
{
	char	*expanded;

	if (check_curly_braces(line))
	{
		*bad_sub = 1;
		g_vars.exit_status = 1;
		return (line);
	}
	expanded = substitute_var(line);
	free(line);
	return (expanded);
}

int	read_heredoc(char *del, char **line)
{
	*line = readline(">");
	if (g_vars.sig_c == 1)
		return (g_vars.sig_c = 2, 1);
	if (NULL == *line)
		return (1);
	if (!ft_strcmp(*line, del))
	{
		free(*line);
		return (1);
	}
	return (0);
}

int	treat_heredoc(char *del, int fd, int sub_var)
{
	char	*line;
	int		bad_sub;

	bad_sub = 0;
	signal(SIGINT, heredoc_sig);
	while (1)
	{
		if (read_heredoc(del, &line))
			break ;
		if (sub_var == 0)
			line = expand_heredoc(line, &bad_sub);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	signal(SIGINT, sig_handler);
	free(del);
	if (bad_sub)
		return (ft_putstr_fd(" : bad substitution\n", 2), 1);
	return (0);
}

int	open_heredoc(t_redirection *red)
{
	char	*del;
	int		sub_var;
	int		fd[2];

	if (g_vars.sig_c == 2)
		return (1);
	if (pipe(fd))
		return (printf("Error in pipe();\n"), 1);
	sub_var = ft_char_in('\'', red->file_name) + ft_char_in('"',
			red->file_name);
	del = trim_str(ft_strdup(red->file_name));
	if (treat_heredoc(del, fd[1], sub_var))
		return (1);
	close(fd[1]);
	if (g_vars.sig_c == 2)
	{
		close(fd[0]);
		red->fd = 0;
		return (1);
	}
	red->fd = fd[0];
	return (0);
}
