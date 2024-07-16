/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:29:04 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:17 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

t_global_vars	g_vars;

void	sig_handler(int sig) {
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
 * SPLIT THE COMMAND BY | PIPE
 * TRIM EACH COMMAND PIPE
 * WAIT THE COMMANDS TO FINISH EXECUTING
 */
void	process_command(char *line)
{
	char	**pipes;
	int		i;

	pipes = ft_split(line, '|');
	if (NULL == pipes)
		return ;
	i = 0;
	while (pipes[i])
	{
		pipes[i] = trim_and_free(pipes[i]);
		++i;
	}
	if (split_len(pipes) == 1)
		exec_simple_cmd(pipes[0]);
	else
		execute_pipes(pipes);
	free_split(pipes);
}

void	init_g_vars(char **envp)
{
	g_vars.env = NULL;
	g_vars.envp = envp;
	g_vars.exit_status = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*read_line;

	(void)ac;
	(void)av;
	init_g_vars(envp);
	init_env();
	signal(SIGINT, sig_handler);
	while (1)
	{
		read_line = readline("\033[1;32mminiSHELL :)=> \033[0m");
		if (NULL == read_line)
			break ;
		add_history(read_line);
		read_line = trim_and_free(read_line);
		if (!closed_quotes(read_line))
			return (free(read_line), free_env(),printf("QUOTES NOT CLOSED"), 0);
		read_line = parse_command_vars(read_line);
		if (!ft_strcmp(read_line, "exit"))
			break ;
		process_command(read_line);
		free(read_line);
	}
	rl_clear_history();
	free(read_line);
	free_env();
	return (0);
}
