/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:55 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/20 15:45:53 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Adds arguments to args (args already has MAX_INPUT time *args)
t_cmd	*ft_add_args(t_cmd *new, t_token *token)
{
	int	i;

	i = 0;
	while (new->args[i])
		i++;
	if (i >= MAX_INPUT - 1)
	{
		printf("Too many Arguments\n");
		return (NULL);
	}
	new->args[i] = ft_strdup(token->value);
	if (!(new->args[i]))
	{
		printf("Argument allocation failed\n");
		return (NULL);
	}
	return (new);	
}

// Adds command to cmd/arg and checks for already existing commands
t_cmd	*ft_add_cmd(t_cmd *new, t_token *token)
{
	if (!new->cmd)
	{
		new->cmd = ft_strdup(token->value);
		if (!new->cmd)
		{
			printf("Command duplication failed\n");
			return (NULL);
		}
	}
	return (ft_add_args(new, token));
}

// Adds next token->value to infile and it checks access too
t_cmd	*ft_add_infile(t_cmd *new, t_token **token)
{
	if (!(*token)->next)
	{
		printf("No infile after redirect in\n");
		return (NULL);
	}
	if (new->infile)
		free(new->infile);
	*token = (*token)->next;
	if (access((*token)->value, F_OK | R_OK) != 0)
	{
		perror("Invalid infile");
		return (NULL);
	}
	new->infile = ft_strdup((*token)->value);
	if (!new->infile)
	{
		printf("Infile duplication failed\n");
		return (NULL);
	}
	return (new);
}

 // Adds next token->value to outfile, it checks access and assigns append
t_cmd	*ft_add_outfile(t_cmd *new, t_token **token, bool append)
{
	if (!(*token)->next)
	{
		printf("No outfile after operator\n");
		return (NULL);
	}
	if (new->outfile)
		free(new->outfile);
	*token = (*token)->next;
	if (access((*token)->value, F_OK) == 0 && access((*token)->value, W_OK) != 0)
	{
		perror("Outfile is not writable");
		return (NULL);
	}
	new->outfile = ft_strdup((*token)->value);
	if (!new->outfile)
	{
		printf("Outfile duplication failed\n");
		return (NULL);
	}
	new->append = append;
	return (new);
}

// Adds next token->value to heredoc_delim
t_cmd	*ft_add_heredoc(t_cmd *new, t_token **token)
{
	if (!(*token)->next)
	{
		printf("No delimiter after heredoc\n");
		return (NULL);
	}
	if (new->heredoc_delim)
		free(new->heredoc_delim);
	*token = (*token)->next;
	new->heredoc_delim = ft_strdup((*token)->value);
	if (!new->heredoc_delim)
	{
		printf("Heredoc delimiter duplication failed\n");
		return (NULL);
	}
	return (new);	
}
