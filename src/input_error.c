/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:28:00 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/20 14:18:03 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unclosed_quotes(char *input)
{
	(void)input;
	return (0);
}

int	input_error(char *input, int *exit_status, t_env *minienv)
{
	(void)exit_status;
	(void)minienv;
	if (!*input || unclosed_quotes(input))
		return (free(input), TRUE);
	return (FALSE);
}