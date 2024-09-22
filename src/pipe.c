/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:47:41 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/22 19:32:02 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	has_pipe(char *str)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (*str == '|')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int	pipe_start(char *input)
{
	if (*input == '|')
		return (syntax_error("|"));
	return (FALSE);
}

char	*get_next_pipe(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str = skip_quotes(str);
		if (*str == '|')
			return (str);
		str++;
	}
	return (NULL);
}

//Checks if pipeline is empty
int	empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(input);
	if (!next_pipe)
		return (FALSE);
	next_pipe++;
	while (*next_pipe == ' ')
		next_pipe++;
	if (*next_pipe == '|')
		return (syntax_error("|"));
	if (*next_pipe == '\0')
		return (ft_putstr_fd(
				"minishell: unclosed pipeline detected\n", 2), TRUE);
	return (empty_pipe(next_pipe));
}