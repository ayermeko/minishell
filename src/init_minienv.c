/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minienv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:58:33 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/28 11:22:06 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
HOME=
HOME_LOCAL=
 */
t_env	*minienv_node(char *name, t_env *minienv)
{
	t_env	*current;
	int		size;

	size = ft_strlen(name);
	current = minienv;
	while (current)
	{
		if (ft_strncmp(name, current->key_pair, size) == 0
			&& (current->key_pair[size] == '=' || current->key_pair[size] == 0))
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*value_only(char *key_pair)
{
	char	*is_command_sign;

	if (!key_pair)
		return (NULL);
	is_command_sign = ft_strchr(key_pair, '=');
	if (!is_command_sign)
		return (ft_strchr(key_pair, 0));
	return (is_command_sign + 1);
}

char	*minienv_value(char *name, t_env *minienv)
{
	t_env	*aux;

	aux = minienv_node(name, minienv);
	if (!aux)
		return (NULL);
	return (value_only(aux->key_pair));
}

void	minienv_add(char *key_pair, t_env **minienv)
{
	t_env	*new_node;

	if (!key_pair)
		return ;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key_pair = ft_strdup(key_pair);
	if (!new_node->key_pair)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (*minienv == NULL)
	{
		*minienv = new_node;
		return ;
	}
	ft_lstadd_back(minienv, new_node);
}

t_env	*init_minienv(char **environ)
{
	t_env	*minienv;
	int		i;

	minienv = NULL;
	i = 0;
	while (environ[i])
		minienv_add(environ[i++], &minienv);
	if (!minienv_node("OLDPWD", minienv))
		minienv_add("OLDPWD", &minienv);
	return (minienv);
}
