/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:57:15 by yesoytur          #+#    #+#             */
/*   Updated: 2025/06/19 20:52:59 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// extract_double_quote helper function
char	*extract_double_inner(char *input, int *i, int start)
{
	char	*joined;
	char	*part;

	joined = NULL;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
			part = extract_expansion(input, i, 0, 0);
		else
		{
			start = *i;
			skip_until_chars(input, i, "\"$");
			part = ft_substr(input, start, (*i) - start);
		}
		joined = strjoin_and_free(joined, part);
	}
	return (joined);
}

void	free_double(char **args)
{
	char	**current;

	if (!args)
		return ;
	current = args;
	while (*current)
		free(*current++);
	free(args);
}

char	*dollar_expansion_inner(char *input, int *i, int start)
{
	char	*name;
	char	*value;

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
