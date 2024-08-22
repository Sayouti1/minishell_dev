/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:37 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:39 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	ft_concat_env_var(char *var)
{
	int		i;
	char	**key_value;
	int		x;

	i = 0;
	while (var && var[i] && var[i] != '=')
		++i;
	if (i < 2 || !var[i] || var[i - 1] != '+')
		return (0);
	if (var[i] == '=' && (!ft_isalnum(var[i - 1]) && var[i - 1] != '+') && reset_fd())
		return (printf("export: `%s': not a valid identifier\n", var),
			set_exit_status(1), 1);
	key_value = split_on_two(var, "+");
	if (NULL == key_value)
		return (set_exit_status(1), 1);
	x = 0;
	if (key_value[1])
		x = 2;
	key_value[1] = string_concat(ft_strdup(get_env_v1(key_value[0])),
			ft_strdup(key_value[1] + x));
	if (!ft_env_replace(key_value[0], key_value[1]))
		add_to_env(ft_strdup(key_value[0]), ft_strdup(key_value[1]), 1);
	free_split(key_value);
	return (1);
}

int	ft_export(char **var)
{
	char	**key_value;
	int		i;
	int		x;

	i = 0;
	while (var && var[i])
	{
		if (ft_concat_env_var(var[i]) && ++i)
			continue ;
		key_value = split_on_two(var[i++], "=");
		if (NULL == key_value)
			return (set_exit_status(1), 1);
		x = 0;
		if (key_value[1])
			x = 1;
		if (!ft_env_replace(key_value[0], key_value[1] + x))
			add_to_env(ft_strdup(key_value[0]), ft_strdup(key_value[1] + x),
				ft_char_in('=', var[i - 1]));
		free_split(key_value);
	}
	return (set_exit_status(0), 0);
}

void	ft_print_export(void)
{
	t_env	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		printf("export %s", tmp->key);
		if (tmp->value)
			printf("=\"%s\"\n", tmp->value);
		tmp = tmp->next;
	}
	set_exit_status(0);
}
