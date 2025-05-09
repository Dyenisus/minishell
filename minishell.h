/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:34:54 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/09 14:13:48 by yesoytur         ###   ########.fr       */
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

extern int	g_exit_status;

typedef enum e_token_type
{
	T_UNKNOWN,
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
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
t_token	*assign_token_value(char *value);
void	print_tokens(t_token *head);

// parse functions

int		ft_isspace(char c);
void	skip_spaces(const char *input, int *i);
void	skip_till_quote_and_dolar(char *input, int *i);
void	skip_till_special(char *input, int *i);
int		is_operator(char c);
int		is_valid_word_start(char c);
char	*strjoin_and_free(char *s1, char *s2);
char	*extract_single_quote(char *input, int *i, int start);
char	*extract_expansion(char *input, int *i, int start);
char	*extract_double_quote(char *input, int *i, int start);
char	*extract_word(char *input, int *i, int start);
t_token	*tokenize_word(char *input, int *i);

t_token	*tokenize(char *input);

#endif

// extractor functions will be divided
// skip functions may need some clenup
// double quote function needs some improvements
// when all of this is done tokenize_oprator() is needed