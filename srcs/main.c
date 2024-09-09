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
	g_vars.sig_c = 0;
	g_vars.tmp_file = 0;
	g_vars.parent = 1;
	g_vars.fd_collectors = NULL;
	g_vars.std_in = dup(0);
	g_vars.std_out = dup(1);
	g_vars.garbage_coll = NULL;
}

// void	main_loop(void)
// {
// 	char		*line;
// 	t_token		*tokens;
// 	t_token		*ntokens;
// 	t_command	*command;

// 	command = NULL;
// 	while (1)
// 	{
// 		sig_init();
// 		line = readline("minishell :)=> ");
// 		if (!line && printf("HIi\n"))
// 			break ;
// 		if (check_line(&line))
// 			continue ;
// 		add_history(line);
// 		tokens = check_and_token(line);
// 		if (!tokens)
// 			continue ;
// 		command = NULL;
// 		if (ft_ambiguous_err(tokens))
// 			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
// 		if (error_heredoc(tokens))
// 		{
// 			ft_putstr_fd("minishell: maximum here-document count exceeded\n",
// 				2);
// 			free_token(tokens);
// 			exit(2);
// 		}
// 		ntokens = expand_var(tokens);
// 		free_token(tokens);
// 		if (!ntokens)
// 			printf("token is NULL go solve it \n");
// 		token_to_command_convert(ntokens, &command);
// 		process_command(command);
// 		free_cmds(command);
// 		free_token(ntokens);
// 	}
// }

void	main_loop(void)
{
	char		*line;
	t_command	*command;

	command = NULL;
	while (1)
	{
		sig_init();
		line = readline("minishell :)=> ");
		if (!line)
			break ;
		if (!check_line(&line))
		{
			add_history(line);
			process_line(line, &command);
		}
		if (!line)
			free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	init_g_vars(envp);
	init_env();
	main_loop();
	rl_clear_history();
	free_env();
	return (0);
}
