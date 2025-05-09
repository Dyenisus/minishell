/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:24 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/09 13:31:57 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Initialize token
t_token	*init_token(void)
{
	t_token	*head;

	head = ft_calloc(1 ,sizeof(t_token));
	if (!head)
	{
		printf("Token can not be initialized\n");
		return (NULL);
	}
	return (head);
}

// Free token/tokens
void	free_token(t_token *head)
{
	t_token *temp;
	t_token *next;

	temp = head;
	while (temp)
	{
		next = temp->next;
		if (temp->value)
			free(temp->value);
		free(temp);
		temp = next;
	}
}

// Add token back
void	add_token(t_token *head, t_token *new)
{
	t_token	*prev;

	if (!head || !new)
		return ;
	prev = head;
	while (prev->next)
		prev = prev->next;
	prev->next = new;
}

// Init and assign token
t_token	*assign_token_value(char *value)
{
	t_token	*new;

	new = init_token();
	if (!new)
		return (NULL);
	if (!value)
	{
		free(new);
		return (NULL);
	}
	new->value = value;
	return (new);
}

// Print tokens (not neccesary)
void	print_tokens(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp)
	{
		printf("%s\n", temp->value);
		temp = temp->next;
	}
}
