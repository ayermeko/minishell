/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:22:27 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/22 14:43:15 by ayermeko         ###   ########.fr       */
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

void	close_extra_fds(void)
{
	int	last_open_fd;

	last_open_fd = open("/tmp/last_fd", O_RDWR | O_CREAT, 0666);
	while (last_open_fd > 2)
		close(last_open_fd--);
}

void	close_all_fds(void)
{
	close_extra_fds();
	close(0);
	close(1);
	close(2);
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
