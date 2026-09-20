#include "../../../include/include.h"

/*
 * Built-ins are dispatched here instead of being mixed into the executor.
 * This keeps command lookup independent from process/pipe setup and makes
 * adding a built-in a single-table-entry change.
 */
typedef void (*t_builtin_fn)(t_command *cmd, int piped);

static void	run_cd(t_command *cmd, int piped)
{
	(void)piped;
	exec_cd(cmd->args);
}

static void	run_echo(t_command *cmd, int piped)
{
	(void)piped;
	exec_echo(cmd);
}

static void	run_export(t_command *cmd, int piped)
{
	(void)piped;
	exec_export(cmd);
}

static void	run_unset(t_command *cmd, int piped)
{
	(void)piped;
	exec_unset(cmd);
}

static void	run_env(t_command *cmd, int piped)
{
	(void)piped;
	exec_env(cmd);
}

static void	run_pwd(t_command *cmd, int piped)
{
	(void)cmd;
	(void)piped;
	pwd();
}

static void	run_exit(t_command *cmd, int piped)
{
	ft_exit(cmd->args, piped);
}

typedef struct s_builtin
{
	char			*name;
	t_builtin_fn	fn;
} t_builtin;

static const t_builtin g_builtins[] = {
	{"echo", run_echo},
	{"export", run_export},
	{"unset", run_unset},
	{"env", run_env},
	{"cd", run_cd},
	{"pwd", run_pwd},
	{"exit", run_exit},
	{NULL, NULL}
};

int	command_handler(t_command *cmd, int piped)
{
	int	i;

	if (!cmd || !cmd->command)
		return (0);
	i = 0;
	while (g_builtins[i].name)
	{
		if (!ft_strcmp(cmd->command, g_builtins[i].name))
		{
			g_builtins[i].fn(cmd, piped);
			return (1);
		}
		i++;
	}
	return (0);
}
