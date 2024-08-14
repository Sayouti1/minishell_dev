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

t_token *check_and_token(char *line)
{
	char *line_trim ;
	t_token *tokens;

	tokens = NULL;
	line_trim = line;
	line_trim = ft_strtrim(line, " \t\n\v\r");
	free(line);
	if (!line_trim)
		return (NULL);
	if (is_syntaxe_cmd(line_trim))
	{
		free(line_trim);
		return (NULL);
	}
	printf("%s\n", line_trim);
	tokens = token_line(line_trim);
	free(line_trim);
	return (tokens);
}
void ft_printToken(t_token *tokens)
{
	t_token *tmp;
	tmp = tokens;
	while (tmp->next)
	{
		printf("value --> %s | type ---> %d \n\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}
void main_loop(void)
{
	char *line;
	t_token *tokens;

	while (1)
	{
		line = readline("miniSHELL--> ");
		if (!line)
			break;
		if(check_line(&line))
			continue;
		add_history(line);
		// check all errors in line like |--> start with the pipe (|) or Error in the Quotes all error 
		//	and lexer token is nothing woring this func { check_and_token }

		tokens = check_and_token(line);
		if (!tokens)
			ft_putstr_fd("Error in the return of the token\n", 2);
		if (tokens)
		{
			ft_printToken(tokens);
			// tokens like |>>>  |"ls"| --next---> |"-al"| --> "|" ---> |"cat"| --> "-e" --> ">" --> "file"
			//save_cmd(&tokens);
		}
		printf("End\n");
	}
}



int	main(int ac, char **av, char **envp)
{
	t_command	*command;
	//char		*read_line;

	(void)ac;
	(void)av;
	command = NULL;
	init_g_vars(envp);
	init_env();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);

	// ✅ CREATE FAKE COMMANDS TO TEST EXECUTION ⬇
	//fake_commands(&command);

// 	while (1)
// 	{
// 		read_line = readline("Minishell=> ");
// 		if (NULL == read_line)
// 			break ;
// 		// if (check_Qoute(read_line))
// 		// 	return (free(read_line), 0);
// 		// lexer_cmd(&command);
// 		if (!closed_quotes(read_line))
// 			return (free(read_line), free_env(),printf("QUOTES NOT CLOSED"), 0);
// 		// printf("2\n");
// 		// if (!ft_strcmp(read_line, "exit"))
// 		// 	break ;
// 		printf("3\n");
// // --------------------------------------
//         int num_tokens = 0;

//         char **tokens = split_by_pipe(read_line, &num_tokens, '|');
//         if (!tokens)
// 			return 1;
	
// 		int i = 0;
// 		int j;
//     	while ( i < num_tokens) {
// 			int nb = 0;
// 			printf("command %d:|-------> %s\n", i + 1, tokens[i]);
// 			char **words = split_by_pipe(tokens[i], &nb, ' ');
// 			j = 0;
// 			while (j < nb)
// 			{
// 				//stocker_cmd(&command);
//         		printf("%d:|-------> %s\n", j + 1, words[j]);
// 				j++;
// 			}
//         	free(tokens[i]);
// 			i++;
//     	}
//     	free(tokens);
// 	//exit(1);
// // ----------------
			
// 		add_history(read_line);
// 		treat_commands(read_line, &command);
// 		free(read_line);
// 		process_command(command);
// 		free_cmds(command);
// 		command = NULL;
// 	}
	main_loop();
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