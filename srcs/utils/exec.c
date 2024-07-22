/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:27 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:31 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

char	*ft_strjoin_prefixed(char *s1, char c, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (NULL == s1 || NULL == s2)
		return (NULL);
	i = (int)ft_strlen(s1) + (int)ft_strlen(s2) + 2;
	join = (char *)malloc(sizeof(char) * i--);
	if (NULL == join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		join[j++] = s1[i++];
	join[j++] = c;
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}

/*
 * ✅ ❌Norminette
 */
int	execute_command(char **split)
{
	char	*fullpath;
	char	*curr_dir;
	pid_t	pid;
	char	**exec_arg;

	curr_dir = getcwd(NULL, 0);
	if (NULL == curr_dir && (split[0] && split[0][0] != '/'))
		return (printf("getcwd error!\n"), set_exit_status(1));
	fullpath = get_correct_path(split, curr_dir);
	free(curr_dir);
	if (NULL == fullpath)
		return (printf("COMMAND NOT FOUND : %s\n", split[0]), set_exit_status(127));
	if (access(fullpath, F_OK))
		return (printf("NO SUCH FILE OR DIRECTORY !!\n"), free(fullpath), set_exit_status(1));
	if (access(fullpath, X_OK))
		return (printf("PERMISSION DENIED : !!\n"), free(fullpath), set_exit_status(126));
	pid = fork();
	if (pid == 0)
	{
		exec_arg = get_exec_arg(fullpath, split[1]);
		if (NULL == exec_arg)
			return (1);
		if (execve(fullpath, exec_arg, g_vars.envp) == -1)
		{
			printf("CANNOT EXECUTE COMMAND : %s, [%s]\n", split[0], fullpath);
			free_split(exec_arg);
			set_exit_status(1);
			exit(1);
		}
	}
	else
		wait(&g_vars.exit_status);
	free(fullpath);
	return (set_exit_status(g_vars.exit_status));
}

void	execute_built_in(t_command *cmd)
{
	if (!ft_strcmp(cmd->command, "echo"))
	{
		if (cmd->args)
			ft_echo(cmd->args);
		else
			printf("\n");
		set_exit_status(0);
	}
	else if (!ft_strcmp(cmd->command, "cd"))
		cd(cmd->args);
	else if (!ft_strcmp(cmd->command, "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->command, "export"))
	{
		if (cmd->args)
			ft_export(cmd->args);
		else
			ft_print_export();
	}
	else if (!ft_strcmp(cmd->command, "unset"))
	{
		if (cmd->args)
			ft_unset(cmd->args);
	}
	else if (!ft_strcmp(cmd->command, "env"))
	{
		if (NULL == cmd->args)
			ft_env();
		else
			set_exit_status(127);
	}
	else if (!ft_strcmp(cmd->command, "exit"))
		ft_exit(cmd->args);
}

void	external_command(t_command *cmd) {
	int	pid;

	pid = fork();
	if (0 == pid)
	{
		execve(cmd->command, cmd->args, g_vars.envp);
		printf("ERROR IN EXECVE EXTERNAL CMD\n");
		exit(1);
	}
	wait(&g_vars.exit_status);
	set_exit_status(g_vars.exit_status);
}

/*
int open_heredoc(t_command *cmd)
{
    char    buff[1000];
    int     byte_read;
    char    *tmp;
    int     fds[2];

    tmp = ft_strjoin(cmd->redirection->file_name, "\n");
    cmd->redirection->file_name = tmp;
    byte_read = 1;
    pipe(fds);
    while(1)
    {
        byte_read = read(0, buff, 1000);
        if (byte_read <= 0 || !ft_strncmp(buff, cmd->redirection->file_name,
                    ft_strlen(cmd->redirection->file_name)))
            break ;
        write(fds[1], buff, byte_read);
    }
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    cmd->redirection->fd = fds[0];
    return (0);
}
 */

char	*ft_strjoin_gnl(char *old_line, char *buff)
{
    int		i;
    int		j;
    char	*new_line;

    j = ft_strlen(buff) + ft_strlen(old_line);
    new_line = (char *)malloc(sizeof(char) * (j + 1));
    if (!new_line)
    {
        free(old_line);
        return (NULL);
    }
    i = 0;
    j = 0;
    while (old_line && old_line[i])
        new_line[j++] = old_line[i++];
    i = 0;
    while (buff[i])
        new_line[j++] = buff[i++];
    new_line[j] = '\0';
//    if (old_line)
//        free(old_line);
    return (new_line);
}

char	*get_dollar_key_v1(char *line, int *i)
{
    int		j;
    int		k;
    char	*key;

    j = *i + 1;
    while (line[j] && line[j] != ' ' && line[j] != '$' && line[j] != '\''
           && line[j] != '"' && line[j] != '\n')
        j++;
    key = (char *)malloc(sizeof(char) * (j - *i));
    if (NULL == key)
        return (NULL);
    k = 0;
    (*i)++;
    while (*i < j && line[*i])
        key[k++] = line[(*i)++];
    key[k] = '\0';
    return (key);
}



char *substitute_var(char *str)
{
    int     i;
    char    *concat;
    char    *key;

    if (NULL == str)
        return (NULL);
    concat = NULL;
    i = 0;
    while(str[i])
    {
        while (str[i] && str[i] != '$')
            concat = char_concat(concat, str[i++]);
        if (str[i] == '$')
        {
            key = get_dollar_key_v1(str, &i);
            concat = string_concat(concat, ft_strdup(get_env_v1(key)));
            free(key);
        }
    }
    return (concat);
}

int check_curly_braces(char *str)
{
    int open_curly_braces;
    int i;

    if (!str)
        return (1);
    open_curly_braces = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '{')
            open_curly_braces = 0;
    }
    return (0);
}
int open_heredoc(t_command *cmd)
{
    char        buff[1000];
    size_t      byte_read;
    char        *del;
    int         fds[2];

    del = char_concat(cmd->redirection->file_name, '\n');
    //free(cmd->redirection->file_name)
    cmd->redirection->file_name = NULL;
    while (1)
    {
        byte_read = read(0, buff, 1000);
        buff[byte_read] = '\0';
        if (byte_read <= 0 || !ft_strncmp(buff, del, ft_strlen(del)))
            break ;
        cmd->redirection->file_name = ft_strjoin_gnl(cmd->redirection->file_name, buff);
    }
    pipe(fds);
    if (!ft_char_in('\'', del) && !ft_char_in('"', del)) {
        if (check_curly_braces(cmd->redirection->file_name))
        {
            return (printf("bad substitution\n"), 1);
        }
        cmd->redirection->file_name = substitute_var(cmd->redirection->file_name);
    }
    write(fds[1], cmd->redirection->file_name, ft_strlen(cmd->redirection->file_name));
    close(fds[1]);
    cmd->redirection->fd = fds[0];
    return (dup2(cmd->redirection->fd, 0), 0);
}

// grep 10 > greep.txt | sort < greep.txt -r | uniq
void	exec_simple_cmd(t_command *cmd)
{
	if (cmd->redirection != NULL)
	{
		if (cmd->redirection->type == OUTPUT || cmd->redirection->type == APPEND)
			dup2(cmd->redirection->fd, 1);
		else if (cmd->redirection->type == INPUT)
			dup2(cmd->redirection->fd, 0);
		else if (cmd->redirection->type == HEREDOC)
            open_heredoc(cmd);
		close(cmd->redirection->fd);
	}

	if (built_in(cmd->command))
		execute_built_in(cmd);
	else
        external_command(cmd);
}

