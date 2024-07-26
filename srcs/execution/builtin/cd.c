/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:29 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:28:37 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	cd_home(char *home)
{
	home = get_env_v1("HOME");
	if (NULL == home)
		return (printf("cd: HOME not set\n"), set_exit_status(1));
	if (chdir(home))
		return (printf("%s : No such file or directory\n", home),
			set_exit_status(1));
	return (set_exit_status(0));
}

/*
 *cd ✅
 *norminette 25 line ❌
 */
int	cd(char **split)
{
	char	*home;
	char	*full_path;

	home = NULL;
	if (split_len(split) > 1)
		return (printf("cd: too many arguments\n"), set_exit_status(1));
	if (NULL == split[0] || (split[0] && split[0][0] == '~' && !split[0][1]))
		return (cd_home(home));
	if (split[0][0] == '/')
	{
		if (chdir(split[0]))
			return (printf("cd: %s: No such file or directory\n", split[0]),
				set_exit_status(1));
		return (set_exit_status(0));
	}
	home = getcwd(NULL, 0);
	full_path = ft_strjoin_prefixed(home, '/', split[0]);
	if (NULL == full_path)
		return (set_exit_status(1));
	if (chdir(full_path))
		return (printf("cd: %s: No such file or directory\n", split[0]),
			free(full_path),
			set_exit_status(1));
	return (free(full_path), set_exit_status(0));
}
