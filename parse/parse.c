/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:39:38 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/10 19:51:37 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Parent Process for parsing
t_token	*parse(char *input)
{
	t_token	*head;

	head = tokenize(input);
	if (!head)
	{
		printf("tokenize error: input can not be tokenized\n");
		return (NULL);
	}
	if (!lexer(head))
	{
		free_token(head);
		return (NULL);
	}
	return (head);
}
