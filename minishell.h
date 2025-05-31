/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoyturstudent.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:34:54 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/31 18:40:35 by yesoytur         ###   ########.fr       */
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
# include <stdbool.h>
# include <limits.h>
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
	bool			quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**infile;
	char			**outfile;
	bool			*append;
	int				out_count;
	char			*heredoc_delim;
	struct s_cmd	*next;
}	t_cmd;

// signal handle
// void	sigint_handler(int sig);

// token functions

t_token	*init_token(void);
void	free_token(t_token *head);
void	add_token(t_token *head, t_token *new);
t_token	*assign_token(char *value, bool *quoted);
void	print_tokens(t_token *head);

// cmd functions

void	free_cmd(t_cmd *head);
t_cmd	*init_cmd(void);
void	add_cmd(t_cmd *head, t_cmd *new);
void	print_cmds(t_cmd *cmd);

// parse functions

int		ft_isspace(char c);
int		ft_iseq(const char *a, const char *b);
void	free_double(char **args);
void	skip_spaces(const char *input, int *i);
void	skip_until_chars(char *input, int *i, const char *delims);
void	skip_until_specials(char *input, int *i);
int		is_operator(char c);
int		is_valid_word_token(const char *str);
int		is_valid_cmd(const char *cmd);
char	*strjoin_and_free(char *s1, char *s2);
char	*extract_single_quote(char *input, int *i, int start, bool *quoted);
char	*extract_expansion(char *input, int *i, int start);
char	*extract_double_quote(char *input, int *i, int start, bool *quoted);
char	*extract_double_inner(char *input, int *i, int start);
char	*extract_word(char *input, int *i, int start);
t_token	*extract_token(char *input, int *i);
t_token	*tokenize_word(char *input, int *i, bool *quoted);
t_token	*tokenize_operator(char *input, int *i);
t_token	*tokenizer(char *input);
int		lexer(t_token *tokens);
t_cmd	*ft_add_args(t_cmd *new, t_token *token);
t_cmd	*ft_add_cmd(t_cmd *new, t_token *token);
t_cmd	*ft_add_infile(t_cmd *new, t_token **token);
t_cmd	*ft_add_outfile(t_cmd *new, t_token **token, bool append);
t_cmd	*ft_add_heredoc(t_cmd *new, t_token **token);
t_cmd	*converter(t_token *token);
t_cmd	*parse(char *input);

#endif

// extractor functions will be divided
// skip functions may need some clenup
// double quote function needs some improvements
// when all of this is done tokenize_oprator() is needed