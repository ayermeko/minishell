/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:22:27 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/20 21:48:30 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_av_error(char **av)
{
	if (!av || !av[1])
	{
		if (av)
			free_array(av);
		close_all_fds();
		exit(0);
	}
	if (!fits_in_long_long(av[1]))
	{
		free_array(av);
		exit_with_error("exit", "numeric argument required", BUILTIN_MISUSE);
	}
	if (av[2] != NULL)
	{
		free_array(av);
		exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
}