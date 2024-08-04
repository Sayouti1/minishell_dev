/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:33:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:34:00 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../Libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_global_vars
{
	t_env	*env;
	char	**envp;
	int		exit_status;
}					t_global_vars;

extern t_global_vars	g_vars;

enum e_redirection {
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC
};

typedef struct s_redirection {
	int						type; // output | append | input | her_doc
	char					*file_name;
	int						fd;
	struct s_redirection	*next;

}	t_redirection;

typedef struct s_command {
	char *command;
	char **args;

	t_redirection	    *redirection;

	int				    input_fd;
	int				    output_fd;
	int				    error_fd;

	int				    is_piped;
	int				    pipe_read;
	int				    pipe_write;

	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

int	            cd_home(char *home);
int	            cd(char **split);


int	            n_option(int *i, char **str);
void	        ft_echo(char **str);


int		        add_to_env(char *key, char *value);
void	        init_env(void);
char	        *get_env_v1(char *key);
t_env	        *new_node(char *key, char *value);
void	        ft_env(void);
int		        ft_env_replace(char *key, char *new_value);


int		        ft_exit(char **arg);


int		        ft_export(char **var);
void	        ft_print_export(void);


int		        pwd(void);
char	        **get_path_dirs(void);
char	        *bin_in_path(char *bin);


void		    search_and_delete(t_env *iter, char *split);
int			    ft_unset(char **key);


int			    built_in(char *str);


char		    *ft_strjoin_prefixed(char *s1, char c, char *s2);
int		        execute_command(char **split);
void	        execute_built_in(t_command *cmd);
void	        external_command(t_command *cmd);
char	        *ft_strjoin_gnl(char *old_line, char *buff);
char	        *get_dollar_key_v1(char *line, int *i);
char	        *substitute_var(char *str);
int		        check_curly_braces(char *str);
int		        open_heredoc(t_redirection *redirection);
void	        exec_simple_cmd(t_command *cmd);


void	        free_env();
void	        delete_env(t_env *env);
void	        free_split(char **arr);
void			free_cmds(t_command *cmd);


char	        *get_dollar_key(char *line, int *i);
char	        *get_var_dollar(char *line);
char	        *get_correct_path(char *split, char *curr_dir);
char	        **get_exec_arg(char *fullpath, char *split);


char	        *trim_and_free(char *line);
char	        *char_concat(char *line, char c);
char	        *string_concat(char *line, char *str);
char	        *parse_command_vars(char *line);


void	        close_and_dup(int to_dup, int fd, int to_close);
void	        swap_pipes(int *curr_pipes, int *prev_pipes);
void	        not_first_cmd(int i, int *prev_pipes);
int		        execute_pipes(int len, int i, t_command *tmp_cmd);


int		        set_exit_status(int n);


void	        sig_handler(int sig);


int			    ft_char_in(char c, char *str);
char		    **ft_split_del(char const *s, char *del);


int	            ft_isspace(char c);
int	            str_isdigit(char *str);
int	            split_len(char **split);
int	            ft_strcmp(char *s1, char *s2);
char		    **split_on_two(char *line, char *del);


t_redirection	*new_redirection(int type, char	*file_name, int	fd);
t_command		*new_command(char *command, char **args, t_redirection *redirection,
	int is_piped, int pipe_read, int pipe_write);
void			add_to_cmds(t_command **head, t_command *cmd);
int				fake_commands(t_command **command);
void			treat_commands(char *read_line, t_command **command);
char			**fix_cmd_arg(t_command *cmd);


void			init_g_vars(char **envp);
int				list_len(t_command *head);
void			process_command(t_command *command);



#endif
