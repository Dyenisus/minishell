/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:39:38 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/09 14:04:29 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_token	*lex(t_token *head)
// {
// 	;
// }

// Extract token
t_token	*extract_token(char *input, int *i)
{
	// if (is_operator(input[*i]))
	// 	return (tokenize_operator(input, i, 0));
	return (tokenize_word(input, i));
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

// function tokenize(input: char *) -> t_token *:
//     i ← 0
//     tokens ← NULL
//     while input[i] is not null:
//         skip_spaces(input, &i)

//         if input[i] == '\'':
//             token ← parse_single_quote(input, &i)

//         else if input[i] == '"':
//             token ← parse_double_quote(input, &i)

//         else if is_operator(input[i]):
//             token ← parse_operator(input, &i)

//         else if input[i] == '$':
//             if input[i + 1] == '?':
//                 token ← create_token(T_EXIT_STATUS, "$?")
//                 i += 2
//             else:
//                 token ← parse_env_var(input, &i)

//         else:
//             token ← parse_word(input, &i)

//         append_token(&tokens, token)

//     return tokens




// Parent Process for parsing
// t_token	*parse(char *input)
// {
// 	// tokenize
// 	// if tokenize returns NULL return NULL
// 	// lex
// }
