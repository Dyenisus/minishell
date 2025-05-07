/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:39:38 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/07 22:04:12 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Parent Process for parsing
t_token	*parse(char *input)
{
	t_token	*head;

	head = init_token();
	if (!head)
		return (NULL);
	// tokenize
	// lex
}

t_token	*tokenize(char *input, t_token *head)
{
	int		i;

	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (input[i] == '\'')
			;// tokenize for single quote
		else if (input[i] == '"')
			;// tokenize for double quote
		else if (is_operator(input[i]))
			;// tokenize for operator
		else if (input[i] == '$')
			;// tokenize for $
		else
			;// tokenize for word
	}
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