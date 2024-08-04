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

void	init_g_vars(char **envp)
{
	g_vars.env = NULL;
	g_vars.envp = envp;
	g_vars.exit_status = 0;
}

void		process_command(t_command *command)
{
	t_command	*tmp_cmd;
	int			i;

	if (list_len(command) == 1)
		exec_simple_cmd(command);
	else
	{
		i = -1;
		tmp_cmd = command;
		execute_pipes(list_len(command), i, tmp_cmd);
	}
}


int	main(int ac, char **av, char **envp)
{
	t_command	*command;
	char		*read_line;

	(void)ac;
	(void)av;
	command = NULL;
	init_g_vars(envp);
	init_env();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);

	// ✅ CREATE FAKE COMMANDS TO TEST EXECUTION ⬇
	//fake_commands(&command);

	while (1)
	{
		read_line = readline("Minishell=> ");
		if (NULL == read_line)
			break ;
		add_history(read_line);
		treat_commands(read_line, &command);
		free(read_line);
		process_command(command);
		free_cmds(command);
		command = NULL;
	}
	rl_clear_history();
	free_cmds(command);
	free_env();
	return (0);
}








/*
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
		read_line = readline("\033[1;32m└─$minishell[~]->\033[0m");
		if (NULL == read_line)
			break ;
		add_history(read_line);
		read_line = trim_and_free(read_line);
		// if (!closed_quotes(read_line))
		// 	return (free(read_line), free_env(),printf("QUOTES NOT CLOSED"), 0);
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
*/