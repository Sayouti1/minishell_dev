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


	signal(SIGQUIT, sig_handler);
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
	while (tmp)
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
		signal(SIGQUIT, SIG_IGN);
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
			// ls -al | cat -e > file
			// tokens like |>>>  |"ls"|---next---> |"-al"| --> "|" ---> |"cat"| --> "-e" --> ">" --> "file"
			//save_cmd(&tokens);
		}
		printf("End\n");
	}
}



int	main(int ac, char **av, char **envp)
{
	t_command	*command;
	// char		*read_line;

	(void)ac;
	(void)av;
	command = NULL;
	init_g_vars(envp);
	init_env();
	signal(SIGINT, sig_handler);
	main_loop();
	// ✅ CREATE FAKE COMMANDS TO TEST EXECUTION ⬇
	//fake_commands(&command);

	// while (1)
	// {
	// 	read_line = readline("Minishell=> ");
	// 	if (read_line && !read_line[0])
	// 	{
	// 		free(read_line);
	// 		continue ;
	// 	}
	// 	if (NULL == read_line)
	// 		break ;
	// 	add_history(read_line);
	// 	treat_commands(read_line, &command);
	// 	free(read_line);
	// 	process_command(command);
	// 	free_cmds(command);
	// 	command = NULL;
	// }
	rl_clear_history();
	free_cmds(command);
	free_env();
	return (0);
}
