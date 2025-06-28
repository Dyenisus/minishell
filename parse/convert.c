/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:59:48 by yesoytur          #+#    #+#             */
/*   Updated: 2025/06/28 22:29:03 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*convert_inner_specifier(t_token **token, t_cmd *new)
{
	if ((*token)->type == T_WORD && is_valid_cmd((*token)->value))
		return(ft_add_cmd(new, *token));
	else if ((*token)->type == T_WORD)
		return(ft_add_args(new, *token));
	else if ((*token)->type == T_REDIRECT_IN)
		return(ft_add_infile(new, token));
	else if ((*token)->type == T_REDIRECT_OUT)
		return(ft_add_outfile(new, token, false));
	else if ((*token)->type == T_APPEND)
		return(ft_add_outfile(new, token, true));
	else if ((*token)->type == T_HEREDOC)
		return(ft_add_heredoc(new, token));
	else
		return (NULL);
}

// Handles inner loop of convert
t_cmd	*convert_inner(t_token **token)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = init_cmd();
	if (!new)
		return (NULL);
	while (*token && (*token)->type != T_PIPE)
	{
		tmp = convert_inner_specifier(token, new);
		if (!tmp)
		{
			free_cmd(new);
			return (NULL);
		}
		new = tmp;
		(*token) = (*token)->next;
	}
	return (new);
}
// Converts tokens to cmds
t_cmd	*converter(t_token *token)
{
	t_cmd	*head;
	t_cmd	*new;

	head = NULL;
	while (token)
	{
		new = convert_inner(&token);
		if (!new)
		{
			free_cmd(head); 
			return (NULL);
		}
		if (!head)
			head = new;
		else
			add_cmd(head, new);
		if (token && token->type == T_PIPE)
			token = token->next;
	}
	return (head);
}
