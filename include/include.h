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

int					cd(char **split);

int					closed_quotes(char *str);
int					built_in(char *str);

void				ft_echo(char *str);

int					add_to_env(char *key, char *value);
void				init_env();
char				*get_env_v1(char *key);
int					eq_index(char *str);
t_env				*new_node(char *key, char *value);
void				ft_env();
int					ft_env_replace(char *key, char *new_value);

char				*ft_strjoin_prefixed(char *s1, char c, char *s2);
int					execute_command(char **split);
void				execute_built_in(char **arg);
int					execute_pipes(char **pipes);
void				exec_simple_cmd(char *cmd);

int					ft_export(char *var);
void				ft_print_export();

void				free_env();
void				delete_env(t_env *env);
void				free_split(char **arr);

char				*get_dollar_key(char *line, int *i);
char				*get_var_dollar(char *line);
char				*get_correct_path(char **split, char *curr_dir);
char				**get_exec_arg(char *fullpath, char *split);

// char	*get_word(char *str, char c, int *start);
// char	*get_rest_of_line(char *str, int start);

char				**split_on_two(char *line, char *del);

void				init_g_vars(char **envp);
void				sig_handler(int sig);
void				process_command(char *line);

char				*trim_and_free(char *line);
char				*char_concat(char *line, char c);
char				*string_concat(char *line, char *str);
char				*parse_command_vars(char *line);

int					pwd(void);
char				**get_path_dirs();
char				*bin_in_path(char *bin);

int					ft_unset(char *key);

int					str_isdigit(char *str);
int					ft_isspace(char c);
int					split_len(char **split);
int					ft_strcmp(char *s1, char *s2);

int					set_exit_status(int n);

char				**ft_split_del(char const *s, char *del);
int				    ft_char_in(char c, char *str);


int				    ft_exit(char *arg);

#endif
