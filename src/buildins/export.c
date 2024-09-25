/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:18 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/25 13:57:12 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	declare_env(t_env *minienv)
{
	
}

int	builtin_export(char **av, t_env **minienv)
{
	char	*key_pair;
	char	*varname;
	int		exit_status;

	av++;
	exit_status = EXIT_SUCCESS;
	if (!*av)
		return (declare_env(*minienv));
}