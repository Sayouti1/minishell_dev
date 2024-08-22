#include "../include/include.h"

//
// Created by aes-sayo on 8/4/24.
//

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
        redirection->file_name = file_name;
	redirection->fd = fd;
	redirection->next = NULL;
	return (redirection);
}

t_command *new_command(char *command, char **args, t_redirection *redirection)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (NULL == cmd)
		return (NULL);
	cmd->command = command;
	cmd->args = args;
	cmd->redirection = redirection;
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
	/*t_redirection	*red;

	red = new_redirection(HEREDOC, "end", 0);
	red->next = new_redirection(OUTPUT, "hhhh", 0);
*/
	 *command = new_command("echo", ft_split("Hello WOrld", ' '), NULL);
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

void	treat_commands(char *read_line, t_command **command)
{
	char	**split;
	int		i;
	char	**cmd;

	split = ft_split(read_line, '|');
	if (NULL == split)
		return;
	i = -1;
	while (split[++i])
		split[i] = trim_and_free(split[i]);

	i = 0;
	while (split[i])
	{
		cmd = split_on_two(split[i], " \t");
		add_to_cmds(command, new_command(ft_strdup(cmd[0]), ft_split_del(cmd[1], " \t"), NULL));
		free_split(cmd);
		++i;
	}
	free_split(split);
}


char **fix_cmd_arg(t_command *cmd)
{
	char	**new_arg;
	int		i;

	new_arg = (char **)malloc(sizeof(char *) * (split_len(cmd->args) + 2));
	if (NULL == new_arg)
		return (NULL);
	new_arg[0] =  ft_strdup(cmd->command);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_arg[i + 1] = ft_strdup(cmd->args[i]);
		++i;
	}
	new_arg[i + 1] = NULL;
	free_split(cmd->args);
	cmd->args = new_arg;
	return (new_arg);
}