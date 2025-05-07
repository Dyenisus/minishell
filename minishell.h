/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:34:54 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/07 22:31:24 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"

typedef enum e_token_type
{
	T_UNKNOWN,
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
	T_ENV_VAR,
	T_FILE,
	T_EXIT_STATUS,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// signal handle
// void	sigint_handler(int sig);

// token functions
t_token	*init_token(void);
void	free_token(t_token *head);
void	add_token(t_token *head, t_token *new);
void	print_tokens(t_token *head);

// parse functions
int		ft_isspace(char c);
void	skip_spaces(const char *input, int *i);
int		is_operator(char c);
int	is_valid_word_start(char c);

#endif