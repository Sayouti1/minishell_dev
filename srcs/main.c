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

void	init_g_vars(char **envp)
{
	g_vars.env = NULL;
	g_vars.envp = envp;
	g_vars.exit_status = 0;
}

t_redirection	*new_redirection(int type, char	*file_name, int	fd)
{
	t_redirection *redirection;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (NULL == redirection)
		return (NULL);

	redirection->type = type;
	redirection->file_name = file_name;
	if (type == OUTPUT)
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	else if (type == APPEND)
		fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0666);
	else if (type == INPUT)
		fd = open(file_name, O_RDONLY);
	else if (type == HEREDOC)
//		printf("HER_DOC TO BE ADDED LATER , ERROR FD\n");
        redirection->file_name = file_name;
	redirection->fd = fd;
	redirection->next = NULL;
	return (redirection);
}

t_command *new_command(char *command, char **args, t_redirection *redirection,
	int is_piped, int pipe_read, int pipe_write)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (NULL == cmd)
		return (NULL);
	cmd->command = command;
	cmd->args = args;
	cmd->redirection = redirection;
	cmd->is_piped = is_piped;
	cmd->pipe_read = pipe_read;
	cmd->pipe_write = pipe_write;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	add_to_cmds(t_command **head, t_command *cmd) {
	t_command *tmp;

    if (*head == NULL)
    {
        *head = cmd;
        return;
    }
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
    if (cmd)
	    cmd->prev = tmp;
	tmp->next = cmd;
}

int	fake_commands(t_command **command)
{
	t_redirection	*red;

	red = new_redirection(HEREDOC, "ff", 0);
	red->next = new_redirection(OUTPUT, "hhhh", 0);

	 *command = new_command("echo", ft_split_del("hello    \t\t\t\t\t\t  How      are     you", " \t"),
		NULL, 1, 0, 1);
    /*
     *command = new_command("/usr/bin/cat", ft_split("/usr/bin/cat infile.txt", ' '), NULL, 1, 0, 1);
	add_to_cmds(command, new_command("/usr/bin/grep", ft_split("/usr/bin/grep test --color=auto", ' '),
		new_redirection(OUTPUT, "outfile.txt", 0), 1, 0, 1));
	add_to_cmds(command, new_command("echo", ft_split("Another test", '|'),
		new_redirection(APPEND, "outfile.txt", 0), 1, 0, 1));
	 add_to_cmds(command, new_command("/usr/bin/bash", ft_split("/usr/bin/bash b", ' '),
                                      NULL, 0, 0, 1));*/
	return (1);
}

int	list_len(t_command *head)
{
	int	i;

	i = 0;
	while (head)
	{
		++i;
		head = head->next;
	}
	return (i);
}

int	execute_pipes_v2(t_command *cmd, int len)
{
	int			i;
	t_command	*tmp_cmd;
	int			prev_pipes[2];
	int			curr_pipes[2];

	i = 0;
	tmp_cmd = cmd;
	while (i < len)
	{
		if (i != 0)
		{
			prev_pipes[0] = curr_pipes[0];
			prev_pipes[1] = curr_pipes[1];
		}
		if (i != len - 1)
			if (pipe(curr_pipes))
				return (printf("ERROR IN pipe()\n"), 1);
		if (fork() == 0)
		{
			if (i != 0)
			{
				close(prev_pipes[1]);
				dup2(prev_pipes[0], 0);
				close(prev_pipes[0]);
			}
			if (i != len - 1)
			{
				close(curr_pipes[0]);
				dup2(curr_pipes[1], 1);
				close(curr_pipes[0]);
			}
			exec_simple_cmd(tmp_cmd);
			exit(0);
		}
		if (i != 0)
		{
			close(prev_pipes[0]);
			close(prev_pipes[1]);
		}
		tmp_cmd = tmp_cmd->next;
		++i;
	}
	close(curr_pipes[0]);
	close(curr_pipes[1]);
	while (i-- > 0)
		wait(&g_vars.exit_status);
	return (set_exit_status(g_vars.exit_status));
}

// cat file.txt | grep 10 > greep.txt | sort < greep.txt -r | uniq

void		process_command_V1(t_command *command)
{
	if (list_len(command) == 1)
		exec_simple_cmd(command);
	else
		execute_pipes_v2(command, list_len(command));

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

	// ✅ CREATE FAKE COMMANDS TO TEST EXECUTION ⬇
	// cat file.txt | grep 10 > greep.txt | sort < greep.txt -r | uniq
	fake_commands(&command);
	process_command_V1(command);
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