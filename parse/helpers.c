/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:22:02 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/09 13:44:13 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

void	skip_till_quote_and_dolar(char *input, int *i)
{
	while (input[*i] && input[*i] != '"' && input[*i] != '$')
		(*i)++;
}

void	skip_till_special(char *input, int *i)
{
	while (input[*i] && input[*i] != '\'' && input[*i] != '"' &&
		input[*i] != '$' && !ft_isspace(input[*i]) && !is_operator(input[*i]))
		(*i)++;
}
