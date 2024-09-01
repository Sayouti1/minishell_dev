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
		set_exit_status(1);
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
	signal(SIGQUIT, SIG_IGN);
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
		return (printf(" : bad substitution\n"), 1);
	return (0);
}

char	*create_tmp_file(int *fd)
{
	char	*file;

	file = string_concat(ft_strdup("/tmp/minishell_"),
			ft_itoa(g_vars.tmp_file++));
	if (NULL == file)
		return (printf("ERROR: creating tmp_file\n"), NULL);
	*fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (-1 == *fd)
		return (printf("ERROR: cannot open tmp_file\n"), NULL);
	return (file);
}

int	open_heredoc(t_redirection *red)
{
	char	*del;
	int		sub_var;
	int		fd[2];

	if (g_vars.sig_c == 2)
		return (1);
	pipe(fd);
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
	// fd = open(tmp_file, O_RDONLY);
	red->fd = fd[0];
	return (0);
}

// int	treat_heredoc(char *del, int *fds, int sub_var)
// {
// 	char	*line;
// 	int		bad_sub;

// 	bad_sub = 0;
// 	signal(SIGINT, heredoc_sig);
// 	while (1)
// 	{
// 		if (read_heredoc(del, &line))
// 			break ;
// 		if (sub_var == 0)
// 			line = expand_heredoc(line, &bad_sub);
// 		ft_putstr_fd(line, fds[1]);
// 		ft_putchar_fd('\n', fds[1]);
// 		free(line);
// 	}
// 	signal(SIGINT, sig_handler);
// 	free(del);
// 	if (bad_sub)
// 		return (printf(" : bad substitution\n"), 1);
// 	return (0);
// }

// int	open_heredoc(t_redirection *redirection)
// {
// 	char	*del;
// 	int		fds[2];
// 	int		sub_var;

// 	sub_var = ft_char_in('\'', redirection->file_name)
// 		+ ft_char_in('"', redirection->file_name);
// 	del = trim_str(ft_strdup(redirection->file_name));
// 	if (pipe(fds) == -1) {
// 		perror("pipe");
// 		exit(1);
// 	}
// 	if (treat_heredoc(del, fds[1], sub_var) && printf("TREAT_HEREDOC\n"))
// 		return (close(fds[1]), close(fds[0]), 1);
// 	close(fds[1]);
// 	redirection->fd = fds[0];
// 	return (0);
// }
