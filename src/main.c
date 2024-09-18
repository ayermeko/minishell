/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:47:37 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/18 15:58:38 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	minishell(t_env *minishell)
{
	int		exit_status;
	char	*input;
	char	**command;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		/* code */
	}
	return (exit_status);
}

int main(void)
{
	extern char **environ;

	return (minishell(init_minienv(environ)));
}
