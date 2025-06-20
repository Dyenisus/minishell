/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:40 by yesoytur          #+#    #+#             */
/*   Updated: 2025/06/20 22:17:54 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks if the type order is correct
static int	type_order_check(t_token *head)
{
	t_token	*curr;

	if (!head)
		return (1);
	if (head->type != T_WORD)
	{
		printf("minishell: syntax error near unexpected token `%s`\n", head->value);
		return (0);
	}
	curr = head;
	while (curr && curr->next)
	{
		if (curr->type != T_WORD && curr->next->type != T_WORD)
		{
			printf("minishell: syntax error near unexpected token `%s`\n", curr->next->value);
			return (0);
		}
		curr = curr->next;
	}
	if (curr && curr->type != T_WORD)
	{
		printf("minishell: syntax error near unexpected token `newline`\n");
		return (0);
	}
	return (1);
}

// Gets tokens type based on the value
static t_token_type	get_token_type(const char *str)
{
	if (ft_iseq(str, "|") && ft_strlen(str) == 1)
		return (T_PIPE);
	else if (ft_iseq(str, "<<") && ft_strlen(str) == 2)
		return (T_HEREDOC);
	else if (ft_iseq(str, ">>") && ft_strlen(str) == 2)
		return (T_APPEND);
	else if (ft_iseq(str, "<") && ft_strlen(str) == 1)
		return (T_REDIRECT_IN);
	else if (ft_iseq(str, ">") && ft_strlen(str) == 1)
		return (T_REDIRECT_OUT);
	else if (is_valid_word_token(str))
		return (T_WORD);
	else
		return (T_UNKNOWN);
}

// Lexes all tokens (assigns their type)
int	lexer(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->quoted)
			temp->type = T_WORD;
		else
			temp->type = get_token_type(temp->value);
		if (temp->type == T_UNKNOWN)
		{
			printf("minishell: syntax error near unexpected token `%s`\n", temp->value);
			return (0);
		}
		temp = temp->next;
	}
	if (!type_order_check(tokens))
		return (0);
	return (1);
}
