/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:22:30 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/24 17:54:58 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_builtin(char **av, t_env **minienv)
{
	if (is_command(*av, "echo"))
		return (echo(av));
	if (is_command(*av, "pwd"))
		return (pwd());
	if (is_command(*av, "env"))
		return (env(*minienv));
	if (is_command(*av, "export"))
		return (builtin_export(av, minienv));
	if (is_command(*av, "unset"))
		return (unset(av, minienv));
	if (is_command(*av, "cd"))
		return (cd(av, *minienv));
	if (is_command(*av, "exit"))
		return (builtin_exit(av, minienv));
	else
		return (EXIT_FAILURE);
}

int	is_builtin(char *cmd)
{
	if (equal(cmd, "echo"))
		return (TRUE);
	if (equal(cmd, "cd"))
		return (TRUE);
	if (equal(cmd, "pwd"))
		return (TRUE);
	if (equal(cmd, "export"))
		return (TRUE);
	if (equal(cmd, "unset"))
		return (TRUE);
	if (equal(cmd, "env"))
		return (TRUE);
	if (equal(cmd, "exit"))
		return (TRUE);
	return (FALSE);
}