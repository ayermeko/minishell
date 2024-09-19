/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:22:27 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/19 22:00:25 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*trim_spaces(char *input)
{
	char	*result;

	result = trim_spaces_no_free(input);
	free(input);
	return (result);
}

char	*trim_spaces_no_free(char	*input)
{
	int		start;
	int		end;
	char	*result;

	if (!input)
		return (NULL);
	start = 0;
	while (input[start] == ' ')
		start++;
	end = ft_strlen(input) - 1;
	while (end >= start && input[end] == ' ')
		end--;
	result = ft_substr(input, start, end - start + 1);
	return (result);
}
