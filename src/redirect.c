/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:17:22 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/20 21:52:39 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_rposition(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str = skip_quotes(str);
		if (*str == '>' || *str == '<' || *str == 1)
			return (str);
		str++;
	}
	return (str);
}

int	unexpected_token(char *input)
{
	if (input[0] == '<' && input[1] == '<')
		return (syntax_error("<<"));
	else if (input[0] == '>' && input[1] == '>')
		return (syntax_error(">>"));
	input[1] = '\0';
	return (syntax_error(input));
}

int	redirect_error(char *input)
{
	char	*position;

	position = get_rposition(input);
	if (!*position)
		return (FALSE);
	if (position[0] == '<' && position[1] == '<')
		position++;
	else if (position[0] == '>' && position[1] == '>')
		position++;
	position++;
	while (*position == ' ')
		position++;
	if (*position == '\0')
		return (syntax_error("newline"));
	if (*position == '|' || *position == '>' || *position == '<')
		return (unexpected_token(position));
	return (redirect_error(position));
}