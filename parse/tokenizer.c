/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:32 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/09 14:11:51 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Extracts expansion
char	*extract_expansion(char *input, int *i, int start)
{
	char	*name;
	char	*value;

	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	name = ft_substr(input, start, *i - start);
	value = getenv(name);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

// Extracts  single quoted strings, supports adjacent segments
char	*extract_single_quote(char *input, int *i, int start)
{
	char	*joined;
	char	*part;

	joined = NULL;
	while (input[*i] == '\'')
	{
		(*i)++;
		start = *i;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		// Check if quote was closed
		if (input[*i] != '\'')
		{
			printf("syntax error: unclosed quote\n");
			free(joined);
			return (NULL);
		}
		part = ft_substr(input, start, (*i) - start);
		joined = strjoin_and_free(joined, part);
		(*i)++;
	}
	return (joined);
}

// Extracts  double quoted strings, supports adjacent segments and expansion but unclosed quote error message needed
char	*extract_double_quote(char *input, int *i, int start)
{
	char	*joined;
	char	*part;

	joined = NULL;
	while (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
		{
			if (input[*i] == '$')
				part = extract_expansion(input, i, 0);
			else
			{
				start = *i;
				skip_till_quote_and_dolar(input, i);
				part = ft_substr(input, start, (*i) - start);
			}
			joined = strjoin_and_free(joined, part);
		}
		if (input[*i] == '"')
			(*i)++;
		else
			break;
	}
	return (joined);
}

char	*extract_word(char *input, int *i, int start)
{
	start = *i;
	skip_till_special(input, i);
	return (ft_substr(input, start, *i - start));
}

// Tokenizes word 
t_token	*tokenize_word(char *input, int *i)
{
	char	*joined;
	char	*part;

	joined = NULL;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'')
			part = extract_single_quote(input, i, 0);
		else if (input[*i] == '"')
			part = extract_double_quote(input, i, 0);
		else if (input[*i] == '$')
			part = extract_expansion(input, i, 0);
		else
			part = extract_word(input, i, 0);
		if (!part)
		{
			free(joined);
			return (NULL);
		}
		joined = strjoin_and_free(joined, part);
	}
	return (assign_token_value(joined));
}
