/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:23:24 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/30 16:43:33 by yesoytur         ###   ########.fr       */
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
	if (!input[*i]) // Case: end of input after $
		return (ft_strdup("$"));
	if (input[*i] == '$') // Case: double dollar sign
		return (ft_strdup("$"));
	if (!ft_isalpha(input[*i]) && input[*i] != '_') // Case: invalid start
		return (ft_strdup("$"));
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	name = ft_substr(input, start, *i - start);
	value = getenv(name);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

// Extracts  single quoted strings, supports adjacent segments
char	*extract_single_quote(char *input, int *i, int start, bool *quoted)
{
	char	*joined;
	char	*part;

	joined = NULL;
	*quoted = true;
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

// Extracts  double quoted strings, supports adjacent segments and expansion
char	*extract_double_quote(char *input, int *i, int start, bool *quoted)
{
	char	*joined;
	char	*part;

	joined = NULL;
	*quoted = true;
	while (input[*i] == '"')
	{
		(*i)++;
		part = extract_double_inner(input, i, start);
		joined = strjoin_and_free(joined, part);
		if (input[*i] == '"')
			(*i)++;
		else
		{
			printf("syntax error: unclosed double quote\n");
			free(joined);
			return (NULL);
		}
	}
	return (joined);
}

// Extracts word add null check and appropiate error message
char	*extract_word(char *input, int *i, int start)
{
	start = *i;
	skip_until_specials(input, i);
	return (ft_substr(input, start, *i - start));
}

// Extracts token
t_token	*extract_token(char *input, int *i)
{
	bool	quoted;

	quoted = false;
	if (is_operator(input[*i]))
		return (tokenize_operator(input, i));
	return (tokenize_word(input, i, &quoted));
}
