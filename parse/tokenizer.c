/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:32 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/10 00:57:10 by yesoytur         ###   ########.fr       */
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
			part = extract_expansion(input, i, 0);
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

// Tokenizes operator has a segfault that I can't seem to find it yet
t_token	*tokenize_operator(char *input, int *i)
{
	char	*op;

	if ((input[*i] == '>' && input[*i + 1] == '>') ||
		(input[*i] == '<' && input[*i + 1] == '<'))
	{
		op = ft_substr(input, *i, 2);
		*i += 2;
	}
	else
	{
		op = ft_substr(input, *i, 1);
		(*i)++;
	}
	if (!op)
	{
		printf("tokenizer error: operator can not be extracted\n");
		return (NULL);
	}
	return (assign_token(op, false));
}

t_token	*tokenize(char *input)
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
