/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:25:19 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/26 17:19:35 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**minienv_to_envp(t_env *minienv)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (ft_lstsize(minienv) + 1));
	i = 0;
	while (minienv)
	{
		envp[i] = ft_strdup(minienv->key_pair);
		i++;
		minienv = minienv->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	is_path(char *command)
{
	if (*command == '.')
		command++;
	if (*command == '.')
		command++;
	if (*command == '/')
		return (TRUE);
	return (FALSE);
}

static int	is_folder(char *command)
{
	struct stat	statbuf;

	if (stat(command, &statbuf) != 0)
		return (FALSE);
	if (S_ISDIR(statbuf.st_mode))
		return(is_path(command));
	return (FALSE);
}

void	external_exit(char **av, t_env *minienv, int exit_status)
{
	if (exit_status == NOT_EXECUTABLE)
		print_error_msg(*av, NOT_EXECUTABLE_MSG);
	if (exit_status == CMD_NOT_FOUND)
		print_error_msg(*av, CMD_NOT_FOUND_MSG);
	rl_clear_history();
	ft_lstclear(&minienv);
	free_array(av);
	close_all_fds();
	exit(exit_status);
}

int	is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int	execute_external(char **av, t_env *minienv)
{
	char	*path;
	char	**envp;

	if (is_empty(*av))
		external_exit(av, minienv, CMD_NOT_FOUND);
	if (is_folder(*av))
		external_exit(av, minienv, NOT_EXECUTABLE);
	path = get_path(*av, minienv);
	if (path == NULL && (minienv_value("PATH", minienv) != NULL))
		external_exit(av, minienv, CMD_NOT_FOUND);
	else if (path == NULL)
		path = ft_strdup(*av);
	rl_clear_history();
	close_extra_fds();
	envp = minienv_to_envp(minienv);
	free_minienv(&minienv);
	if (execve(path, av, envp) == -1)
		handle_execve_errors(av, path, envp);
	exit(EXIT_SUCCESS);
}