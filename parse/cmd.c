/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:05:32 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/20 15:50:16 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Frees cmd/cmds
void	free_cmd(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = head;
	while (current)
	{
		tmp = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		if (current->heredoc_delim)
			free(current->heredoc_delim);
		if (current->args)
			free_double(current->args);
		free(current);
		current = tmp;
	}
}

// Initializes cmds
t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = ft_calloc(MAX_INPUT, sizeof(char *));
	if (!(new->args))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

// Adds cmds back
void	add_cmd(t_cmd *head, t_cmd *new)
{
	t_cmd	*prev;

	if (!head || !new)
		return ;
	prev = head;
	while (prev->next)
		prev = prev->next;
	prev->next = new;
}

// Prints cmds for debugging
void	print_cmds(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("----\n");
		if (cmd->cmd)
			printf("cmd: %s\n", cmd->cmd);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		if (cmd->infile)
			printf("infile: %s\n", cmd->infile);
		if (cmd->outfile)
			printf("outfile: %s\n", cmd->outfile);
		if (cmd->append)
			printf("append: true\n");
		else if (cmd->outfile)
			printf("append: false\n");
		if (cmd->heredoc_delim)
			printf("heredoc_delim: %s\n", cmd->heredoc_delim);
		printf("----\n");
		cmd = cmd->next;
	}
}
