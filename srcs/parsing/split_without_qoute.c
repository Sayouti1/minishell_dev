#include "../../include/include.h"

char	**split_string(const char *str, char delimiter, int *num_tokens)
{
	int		count;
	char	**result;
	int		start;
	int		token_idx;

	count = 1;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == delimiter)
			count++;
	}
	result = malloc(count * sizeof(char *));
	if (!result)
		return (NULL);
	start = 0;
	token_idx = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == delimiter)
		{
			result[token_idx] = malloc(i - start + 1);
			if (!result[token_idx])
				return (NULL);
			strncpy(result[token_idx], &str[start], i - start);
			result[token_idx][i - start] = '\0';
			start = i + 1;
			token_idx++;
		}
	}
	result[token_idx] = malloc(strlen(str) - start + 1);
	if (!result[token_idx])
		return (NULL);
	strcpy(result[token_idx], &str[start]);
	*num_tokens = token_idx + 1;
	return (result);
}

char	**split_by_pipe(const char *str, int *num_tokens, char c)
{
	char	*buffer;
	char	**result;
	int		result_idx;
	int		buffer_len;
	int		in_single_quote;
	int		in_double_quote;
	int		start;
	char	current_char;

	buffer = malloc(strlen(str) + 1);
	if (!buffer)
		return (NULL);
	strcpy(buffer, str);
	result = malloc(strlen(str) * sizeof(char *));
	if (!result)
		return (NULL);
	result_idx = 0;
	buffer_len = strlen(buffer);
	in_single_quote = 0;
	in_double_quote = 0;
	start = 0;
	for (int i = 0; i <= buffer_len; i++)
	{
		current_char = buffer[i];
		if (current_char == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
		}
		else if (current_char == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
		}
		else if (current_char == c && !in_single_quote && !in_double_quote)
		{
			buffer[i] = '\0';
			result[result_idx] = malloc(i - start + 1);
			if (!result[result_idx])
				return (NULL);
			strcpy(result[result_idx], &buffer[start]);
			result_idx++;
			start = i + 1;
		}
	}
	result[result_idx] = malloc(buffer_len - start + 1);
	if (!result[result_idx])
		return (NULL);
	strcpy(result[result_idx], &buffer[start]);
	*num_tokens = result_idx + 1;
	free(buffer);
	return (result);
}

// int _getwords(char *line)
// {
//     int words;
//     int i;
//     words = 0;
//     i = 0;

//     while (line[i])
//     {

//     }
// }

// char **_split(char *line, char s)
// {
//     char **string;
//     int     size;

//     size = _getwords(line);
//     string = (char *) malloc(sizeof(char *) * size);

// }
