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
	g_vars.std_in = dup(0);
	g_vars.std_out = dup(1);
	g_vars.garbage_coll = NULL;
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
		printf("value --> [%s] | type ---> %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}

void	print_commands(t_command *command)
{
	int				i;
	t_redirection	*red;
	t_command		*cmd;

	i = 0;
	cmd = command;
	while (cmd)
	{
		printf("{\n\tcommand[%d] = [%s],\n", ++i, cmd->command);
		if (cmd->args)
		{
			printf("\targs = {\n");
			int	j = 0;
			while (cmd->args && cmd->args[j])
			{
				printf("\t\t[%d] = [%s],\n", j + 1, cmd->args[j]);
				++j;
			}
			printf("\t}\n");
		}
		red = cmd->redirection;
		if (red)
		{
			printf("\tredirection = {\n");
			while (red)
			{
				printf("\t\ttype = %d, file_name = [%s]\n", red->type, red->file_name);
				red = red->next;
			}
			printf("\t}\n");
		}
		printf("}\n");
		cmd = cmd->next;
	}
}

void main_loop(void)
{
	char *line;
	t_token *tokens;
	t_command	*command;

	command = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		g_vars.sig_c = 0;
		line = readline("\033[1;32mminishell :)=> \033[0m");
		if (!line)
			break;
		if(check_line(&line))
			continue;
		add_history(line);
		tokens = check_and_token(line);
		if (!tokens)
			continue ;
		command = NULL;
		if (ft_ambiguous_err(tokens))
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			exit(1);
			//continue;
			//free_token(tokens);
		}

		// ft_printToken(tokens);
		expand_var(&tokens);
		// ft_printToken(tokens);
		token_to_command_convert(tokens, &command);
		print_commands(command);
		process_command(command);
		free_cmds(command);
		free_token(tokens);
	}
}



int	main(int ac, char **av, char **envp)
{
	t_command	*command;

	(void)ac;
	(void)av;
	command = NULL;
	init_g_vars(envp);
	init_env();
	signal(SIGINT, sig_handler);
	main_loop();
	rl_clear_history();
	free_cmds(command);
	free_env();
	return (0);
}
