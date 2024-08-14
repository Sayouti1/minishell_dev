#include "../../../include/include.h"

void	update_quote_counts(char c, int *s_q_count, int *d_q_count)
{
	if (c == 34)
		(*d_q_count)++;
	else if (c == 39)
		(*s_q_count)++;
}

char *skip_spaces(char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

int is_space(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' 
		|| line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int check_line(char **line)
{
	if (*line[0] == '\0' || _strcmp(*line, "\n", NULL) || is_space(*line))
	{
		free(*line);
		return (1);
	}
	return (0);
}

/**/
int is_invalid_op(char **line)
{
	char *op_st;
	op_st  = *line;
	(*line)++;
	if (*op_st == **line)
		(*line)++;
	*line = skip_spaces(*line);
	if (**line == '\0' || **line == '>' 
		|| **line == '<' || **line == '|')
		return (1);
	return (0);
}

int	_strcmp(char *s_1, char *s_2, char *s_3)
{
	int					a;

	a = 0;
	while (s_1[a] && s_2[a] && s_1[a] == s_2[a])
		a += 1;
	if (a == sizeof_str(s_1, '\0')
		&& a == sizeof_str(s_2, '\0'))
		return (1);
	if (s_3)
		return (_strcmp(s_1, s_3, NULL));
	return (0);
}
int	sizeof_str(char *str, char end)
{
	int			a;

	a = 0;
	while (str && str[a] != '\0' && str[a] != end)
		a += 1;
	return (a);
}