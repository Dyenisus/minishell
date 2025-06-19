/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:12:53 by yesoytur          #+#    #+#             */
/*   Updated: 2025/06/19 21:08:37 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Extracts dollar expansion may need valid expansion checker
char	*dollar_expansion(char *input, int *i, int start)
{
	(*i)++;
	if (!input[*i]) // Case: end of input after $
		return (ft_strdup("$"));
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	if (input[*i] == '$') // Case: double dollar sign
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	if (!ft_isalpha(input[*i]) && input[*i] != '_') // Case: invalid start
		return (ft_strdup("$"));
	else
		return(dollar_expansion_inner(input, i, start));
}

// Extracts tilde expansion
char	*tilde_expansion(char *input, int *i, int start)
{
	char	*path;
	char	*home;
	
	home = getenv("HOME");
	if (!home)
		return (ft_strdup("~"));
	(*i)++;
	if (!input[(*i)]) // ~
		return (ft_strdup(home));
	else if (input[*i] != '/') // ~somegibberish
		return (ft_strdup("~"));
	else // ~/somegibberish
	{
		start = (*i);
		while (input[*i])
			(*i)++;
		path = ft_substr(input, start, *i - start);
		return (strjoin_and_free(ft_strdup(home), path));
	}
}
