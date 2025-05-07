/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:04:02 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/07 22:30:38 by yesoytur         ###   ########.fr       */
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

int	is_valid_word_start(char c)
{
	if (!ft_isprint(c))
		return (0);
	if (ft_isspace(c) || is_operator(c) || c == '$'
		|| c == '"' || c == '\'' || c == ';' || c == '\\')
		return (0);
	return (1);
}
