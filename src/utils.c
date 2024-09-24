/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:22:27 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/24 16:42:54 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fits_in_long_long(char *str)
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

void	redirect_heredoc(char *command)
{
	int		tmp_file_fd;

	tmp_file_fd = open("/tmp/minishell_hd", O_RDONLY);
	if (tmp_file_fd == -1)
	{
		print_perror_msg("open", "/tmp/minishell_hd");
		return ;
	}
	redirect_fd(tmp_file_fd, STDIN_FILENO);
	delete_char(get_spos(command, "\x01"), 1);
}