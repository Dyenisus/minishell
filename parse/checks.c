/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:04:02 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/10 00:37:04 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return ((c == ' ') || (c >= '\t' && c <= '\r'));
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	ft_iseq(const char *a, const char *b)
{
	return (ft_strncmp(a, b, ft_strlen(b) + 1) == 0);
}

int	is_valid_word_token(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		if (ft_isspace(str[i]) || is_operator(str[i]) || str[i] == '$'
			|| str[i] == '"' || str[i] == '\'' || str[i] == ';' || str[i] == '\\')
			return (0);
		i++;
	}
	return (1);
}
