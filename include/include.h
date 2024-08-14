/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:33:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/14 20:34:53 by aez-zoui         ###   ########.fr       */
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

typedef enum s_token_type
{
	TOKEN_WORD, // using for the cmd argm
	TOKEN_PIPE, // using for the pipe cmd
	TOKEN_REDIR_IN, // using like <
	TOKEN_REDIR_OUT, //using like >
	TOKEN_REDIR_APPEND, // using for >>
	TOKEN_REDIR_HEREDOC, // using for <<
} t_token_type;
// tok 
// | >
			// ls -al | cat -e > file
			// tokens like |>>>  |"ls"|---next---> |"-al"| --> "|" ---> |"cat"| --> "-e" --> ">" --> "file"

// ("/bin/ls" , {"/bin/ls", }, )
typedef struct s_token
{
	t_token_type  type; // TOKEN
	char *value;	 // "ls" 
	struct s_token *next; 
}	t_token;

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
	char *command; // TOKEN_WORD 0 
	char **args; // white TYPE == TOKEN_WORND 0

	t_redirection	    *redirection;

	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

// ---------------------------- PARSING -----------------
char **split_by_pipe(const char *str, int *num_tokens, char c);
int closed_quotes(char *str);
void	update_quote_counts(char c, int *s_q_count, int *d_q_count);
char *skip_spaces(char *input);
int is_space(char *line);
int check_line(char **line);
int is_invalid_op( char **input);
int is_syntaxe_cmd(char *line);
int is_closed_qoute(char *line);
int is_invalid_redirection(char *line);
int is_error_misplaced(char *line);
int is_error_logic(char *line);
// -----------------------------LEXER----------------------
void update_quote_status(char c, int *is_quote, char *qoute_char);
t_token *new_token(t_token_type type, char *value);
void    add_token_to_list(t_token **tokens, t_token *new_token);
void free_token(t_token *tokens);
void word_to_token(char **start, char **line, t_token **tokens);
t_token *token_line(char *line);
void    do_words(char **line, t_token **tokens);
void    do_speacil_chars(char **line, t_token **tokens);
char	*ft_strndup(char *src, size_t n);
int	_strcmp(char *s_1, char *s_2, char *s_3);
int	sizeof_str(char *str, char end);
size_t	ft_strnlen(const char *s, size_t maxlen);
void word_to_token(char **start, char **line, t_token **tokens);

// ------------------------------------------------------

void			exec_echo(t_command *cmd);
void			exec_export(t_command *cmd);
void			exec_env(t_command *cmd);
void			exec_unset(t_command *cmd);

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
// int		        execute_command(char **split);
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


// char	        *get_dollar_key(char *line, int *i);
// char	        *get_var_dollar(char *line);
char	        *get_correct_path(char *split, char *curr_dir);
char	        **get_exec_arg(char *fullpath, char *split);


char	        *trim_and_free(char *line);
char	        *char_concat(char *line, char c);
char	        *string_concat(char *line, char *str);
// char	        *parse_command_vars(char *line);


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
