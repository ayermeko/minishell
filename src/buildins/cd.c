/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:08 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/26 19:25:50 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(char **av, t_env *minienv)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (av[1] && av[2])
		return (print_error_msg("cd", "too many arguments"), EXIT_FAILURE);
	if (av[1] && !is_command(av[1], "~"))
		path = av[1];
	else
		path = minienv_value("HOME", minienv);
	if (!path)
		return (print_error_msg("cd", "HOME not set"), 1);
	if (path[0] == 0)
		return (0);
	if (chdir(path) != 0)
		return (print_perror_msg("cd", av[1]), EXIT_FAILURE);
	pwd = minienv_value("PWD", minienv);
	oldpwd = minienv_value("OLDPWD", minienv);
	if (oldpwd && pwd)
		minienv_update("OLDPWD", pwd, minienv);
	if (pwd)
		minienv_update("PWD", getcwd(cwd, PATH_MAX), minienv);
	return (EXIT_SUCCESS);
}
