/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:40 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/07 22:32:57 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_type	get_token_type(const char *str)
{
	if (str[0] == '|')
		return (T_PIPE);
	else if (str[0] == '<' && str[1] == '<')
		return (T_HEREDOC);
	else if (str[0] == '>' && str[1] == '>')
		return (T_APPEND);
	else if (str[0] == '<')
		return (T_REDIRECT_IN);
	else if (str[0] == '>')
		return (T_REDIRECT_OUT);
	else if (str[0] == '$' && str[1] == '?')
		return (T_EXIT_STATUS);
	else if (str[0] == '$')
		return (T_ENV_VAR);
	else if (is_valid_word_start(str[0]))
		return (T_WORD);
	else
		return (T_UNKNOWN);
}
