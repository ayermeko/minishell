/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minienv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:58:33 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/18 14:53:50 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*minienv_node(char *name, t_env *minienv)
{
	t_env	*current;
	int		size;

	size = ft_strlen(name);
	current = minienv;
	while (current)
	{
		if (ft_strncmp(name, current->key_pair, size) == 0 
		&& current->key_pair[size] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

//Return value of *key_pair
// char	*value_only(char *key_pair)
// {
// 	int	i;

// 	i = 0;
// 	while (key_pair[i] != '=' && key_pair[i])
// 		i++;
// 	if (!key_pair[i])
// 		return (NULL);
// 	return (&key_pair[i + 1]);
// }

char *value_only(char *key_pair)
{
    char *equal_sign;

    equal_sign = ft_strchr(key_pair, '=');
    if (!equal_sign)
        return (NULL);
    return (equal_sign + 1);
}

//Return value of *name
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
	t_env	*aux_node;

	new_node = malloc(sizeof(t_env));
	new_node->key_pair = ft_strdup(key_pair);
	new_node->next = NULL;
	if (*minienv == NULL)
	{
		*minienv = new_node;
		return ;
	}
	aux_node = *minienv;
	ft_lstadd_back(&aux_node, new_node);
	// while (aux_node->next != NULL)
	//  	aux_node = aux_node->next;
	// aux_node->next = new_node;
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