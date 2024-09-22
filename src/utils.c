/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:22:27 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/22 20:21:22 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	fits_in_long_long(char *str)
{
	long long	out;
	int			c;
	char		*temp;

	str = trim_spaces_no_free(str);
	if (ft_strlen(str) > 20)
		return (free(str), FALSE);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (free(str), TRUE);
	temp = str;
	if (*str == '-' || *str == '+')
		str++;
	out = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (free(temp), FALSE);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (free(temp), FALSE);
		out = out * 10 + c;
		str++;
	}
	return (TRUE);
}

void	delete_char(char *str, int len)
{
	ft_memmove(str, str + len, ft_strlen(str + len) + 1);
}

void	check_av_error(char **av)
{
	if (!av || !av[1])
	{
		if (av)
			free_array(av);
		close_all_fds();
		exit(0);
	}
	if (!fits_in_long_long(av[1]))
	{
		free_array(av);
		exit_with_error("exit", "numeric argument required", BUILTIN_MISUSE);
	}
	if (av[2] != NULL)
	{
		free_array(av);
		exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
}

long long	ft_atoll(const char *str)
{
	long long	number;
	int			sign;

	number = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (number * sign);
}

int	one_command(char *input, t_env **minienv)
{
	char	**av;
	int		exit_status;
	int		original_fds[2];

	if (*input == 0)
		return (free(input), 0);
	if (!handle_redirects(input, &original_fds[0]))
	{
		restore_original_fds(original_fds);
		free(input);
		return (EXIT_FAILURE);
	}
	av = split_av(input);
	free(input);
	exit_status = 0;
	if (av[0] != NULL)
	{
		if (is_builtin(av[0]))
			exit_status = execute_builtin(av, minienv);
		else
			exit_status = exec_fork_extern(av, *minienv);
	}
	free_array(av);
	restore_original_fds(original_fds);
	return (exit_status);
}