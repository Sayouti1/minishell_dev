/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:53:14 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

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

char	*ft_strjoin_gnl(char *old_line, char *buff)
{
	int		i;
	int		j;
	char	*new_line;

	j = ft_strlen(buff) + ft_strlen(old_line);
	new_line = (char *)malloc(sizeof(char) * (j + 1));
	if (NULL == new_line)
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

char	*char_concat(char *line, char c)
{
	char	*concat;
	int		i;
	int		j;

	i = ft_strlen(line);
	// concat = ft_realloc(line, (i + 2) * sizeof(char));

	concat = (char *)malloc(sizeof(char) * (i + 2));
	if (NULL == concat)
		return (NULL);
	concat[i] = c;
	j = 0;
	i = 0;
	while (line && line[i])
		concat[j++] = line[i++];
	concat[j++] = c;
	concat[j] = '\0';
	free(line);
	return (concat);
}

char	*string_concat(char *line, char *str)
{
	int		i;
	int		j;
	char	*concat;

	i = ft_strlen(str) + ft_strlen(line);
	concat = (char *)malloc(sizeof(char) * (i + 1));
	if (NULL == concat)
		return (NULL);
	i = 0;
	j = 0;
	while (line && line[i])
		concat[j++] = line[i++];
	i = 0;
	while (str && str[i])
		concat[j++] = str[i++];
	concat[j] = '\0';
	free(line);
	free(str);
	return (concat);
}

/*
 * TRIM USER INPUT IN A NEW ALLOCATED STRING,
 * AND RETURN IT , THEN FREE THE OLD READLINE
 */
char	*trim_and_free(char *line)
{
	char	*trimmed;

	if (NULL == line)
		return (NULL);
	if (line[0] == '\0')
		return (line);
	trimmed = ft_strtrim(line, " 	");
	if (NULL == trimmed)
		return (NULL);
	free(line);
	return (trimmed);
}
