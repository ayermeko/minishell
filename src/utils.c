/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:22:27 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/20 20:39:51 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (pipe_start(input) || redirect_error(input))
	{
		*exit_status = 2;
		return (free(input), TRUE);
	}
	return (FALSE);
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


void	builtin_exit(char **av, t_env **minienv)
{
	(void)av;

	rl_clear_history();
	ft_lstclear(minienv);
	ft_putstr_fd("exit\n", 1);
	//check_av_error(av);
	//close_all_fds();
	//exit_status = ft_atoll(av[1]);
	//free_array(av);
	//exit(exit_status);
}

//Checks if *input starts from the pipe
int	pipe_start(char *input)
{
	if (*input == '|')
		return (syntax_error("|"));
	return (FALSE);
}
