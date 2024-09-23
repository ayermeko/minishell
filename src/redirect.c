/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:17:22 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/23 22:37:49 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_spos(char *str, const char *chars_to_find)
{
    while (*str)
    {
        str = skip_quotes(str);
        if (ft_strchr(chars_to_find, *str))
            return (str);
        str++;
    }
    return (NULL);
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

	position = get_spos(input, "><\x01");
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

int	handle_redirects(char *input, int original_fds[2])
{
	char	redirect;
	
	original_fds[0] = NO_REDIRECT;
	original_fds[1] = NO_REDIRECT;
	redirect = *get_spos(input, "><\x01");
	while (redirect)
	{
		if (redirect == '<' && !handle_io(input, original_fds, 0))
			return (FAILED);
		if (redirect == '>' && !handle_io(input, original_fds, 1))
			return (FAILED);
		if (redirect == 1)
		{
			save_original_fd_in(original_fds);
			redirect_heredoc(input);
		}
		redirect = *get_spos(input, "><\x01");
	}
	return (SUCCESS);
}
