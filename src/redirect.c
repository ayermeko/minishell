/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:17:22 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/25 17:05:11 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_original_fds(int original_fds[2])
{
	if (original_fds[0] != NO_REDIRECT)
		redirect_fd(original_fds[0], STDIN_FILENO);
	if (original_fds[1] != NO_REDIRECT)
		redirect_fd(original_fds[1], STDOUT_FILENO);
}

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

char	*get_redirect_position(char *str, char redirect_char)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (*str == redirect_char)
			return (str);
		str++;
	}
	return (str);
}

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

int	handle_redirects(char *input, int original_fds[2])
{
	char	redirect;
	
	original_fds[0] = NO_REDIRECT;
	original_fds[1] = NO_REDIRECT;
	redirect = *(get_rposition(input));
	while (redirect)
	{
		if (redirect == '<' && !handle_io(input, original_fds, STDIN_FILENO))
			return (FAILED);
		else if (redirect == '>' && !handle_io(input, original_fds, STDOUT_FILENO))
			return (FAILED);
		else if (redirect == 1)
		{
			save_original_fd(original_fds, STDIN_FILENO);
			redirect_heredoc(input);
		}
		redirect = *(get_rposition(input));
	}
	return (SUCCESS);
}
