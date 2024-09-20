/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:47:37 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/20 20:20:48 by ayermeko         ###   ########.fr       */
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
	//char	**command;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		signal_handler();
		input = free_spaces(prompt_input(minienv));
		if (input_error(input, &exit_status, minienv))
			continue ;
	}
	return (0);
}

int main(void)
{
	extern char **environ;

	return (minishell(init_minienv(environ)));
}

// niceily sorted file.