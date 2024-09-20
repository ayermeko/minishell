/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:28:00 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/20 18:40:43 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (TRUE);
}

//Checks if *input starts from the pipe
int	pipe_start(char *input)
{
	if (*input == '|')
		return (syntax_error("|"));
	return (FALSE);
}

int	unclosed_quotes(char *input)
{
	char	quote_char;

	quote_char = '\0';
	while (*input)
	{
		if ((*input == '\'' || *input == '"') && quote_char == '\0')
			quote_char = *input;
		else if (*input == quote_char)
			quote_char = '\0';
		input++;
	}
	if (quote_char != '\0')
	{
		ft_putstr_fd("minishell: unclosed quotes detected\n", 2);
		return (TRUE);
	}
	return (FALSE);
}

int	input_error(char *input, int *exit_status, t_env *minienv)
{
	if (!*input || unclosed_quotes(input))
		return (free(input), TRUE);
	if (pipe_start(input))
	return (FALSE);
}