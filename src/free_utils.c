/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:15:39 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/21 17:25:15 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*free_spaces(char *input)
{
	char	*result;

	result = trim_spaces_no_free(input);
	free(input);
	return (result);
}

void	free_array(char **av)
{
	int	i;

	if (!av)
		return ;
	i = 0;
	while (av[i])
	{
		free(av[i]);
		av[i] = NULL;
		i++;
	}
	free(av);
	av = NULL;
}

int	builtin_exit(char **av, t_env **minienv)
{
	int	exit_status;

	rl_clear_history();
	ft_lstclear(minienv);
	ft_putstr_fd("exit\n", 1);
	check_av_error(av);
	close_all_fds();
	exit_status = ft_atoll(av[1]);
	free_array(av);
	exit(exit_status);
}