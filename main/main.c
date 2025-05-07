/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:38:00 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/07 22:06:18 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig);

int	main(int argc, char **argv)
{
	char 	*input;
	t_token	*head;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler); // for ctrl + c (prints newline)
	signal(SIGQUIT, SIG_IGN); // for ctrl + / (does nothing)
	while (1)
	{
		input = readline("minishell> ");
		if (!input) // for ctrl + d (prints exit\n and quits)
		{
			printf("exit\n");
			break ;
		}
		if (!(*input)) // for Enter (reads again)
		{
			free(input);
			continue ;
		}
		add_history(input);
		// parse
		// execute
	}
	free(input);
	return (0);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
