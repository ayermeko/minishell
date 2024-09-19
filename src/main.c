/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:47:37 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/19 21:30:06 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*prompt_input(t_env *minienv)
{
	char	*input;
	
	input = readline("minishell$ ");
	if (!input)
		builtin_exit(NULL, &minienv);
	if (*input)
		add_history(input);
	return (input);
}

static int	minishell(t_env *minienv)
{
	int		exit_status;
	char	*input;
	char	**command;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		signal_handler();
		input = trim_spaces(prompt_input(minienv));
	}
	return (0);
}

int main(void)
{
	extern char **environ;

	return (minishell(init_minienv(environ)));
}
