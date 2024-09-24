/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:58:07 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/24 18:24:13 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}