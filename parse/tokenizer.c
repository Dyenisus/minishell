/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:32 by yesoytur          #+#    #+#             */
/*   Updated: 2025/06/26 20:59:37 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Tokenizes word 
t_token	*tokenize_word(char *input, int *i, bool *quoted)
{
	char	*joined;
	char	*part;

	joined = NULL;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'')
			part = extract_single_quote(input, i, 0, quoted);
		else if (input[*i] == '"')
			part = extract_double_quote(input, i, 0, quoted);
		else if (input[*i] == '$')
			part = extract_dollar(input, i, 0);
		else if (!joined && input[*i] == '~')
			part = extract_tilde(input, i, 0);
		else
			part = extract_word(input, i, 0);
		if (!part)
		{
			free(joined);
			return (NULL);
		}
		joined = strjoin_and_free(joined, part);
	}
	return (assign_token(joined, quoted));
}

// Tokenizes operator
t_token	*tokenize_operator(char *input, int *i)
{
	int		start;
	char	*op;
	bool	quoted;

	quoted = false; 
	start = *i;
	while (input[*i] && is_operator(input[*i]) && !ft_isspace(input[*i]))
		(*i)++;
	op = ft_substr(input, start, *i - start);
	if (!op)
		return (NULL);
	return (assign_token(op, &quoted));
}

// Main tokenizer function
t_token	*tokenizer(char *input)
{
	int		i;
	t_token	*head;
	t_token	*new;

	head = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		new = extract_token(input, &i);
		if (!new)
		{
			free_token(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
			add_token(head, new);
	}
	return (head);
}
