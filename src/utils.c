/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:22:27 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/25 18:14:48 by ayermeko         ###   ########.fr       */
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

int is_command(char *str1, char *str2)
{
    return (ft_strncmp(str1, str2, ft_strlen(str1) + 1) == 0);
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
	delete_char(get_redirect_position(command, 1), 1);
}

char	*create_keypair(char *name, char *value)
{
	char	*key_pair;
	int		key_pair_size;
	int		i;

	key_pair_size = ft_strlen(name) + ft_strlen(value) + 2;
	key_pair = malloc(key_pair_size * sizeof(char));
	i = 0;
	while (*name)
		key_pair[i++] = *name++;
	key_pair[i++] = '=';
	while (*value)
		key_pair[i++] = *value++;
	key_pair[i] = '\0';
	return (key_pair);
}

void	minienv_update(char *name, char *value, t_env *minienv)
{
	t_env	*aux;
	char	*new_pair;

	aux = minienv_node(name, minienv);
	if (!aux)
	{
		new_pair = create_keypair(name, value);
		minienv_add(new_pair, &minienv);
		free(new_pair);
		return ;
	}
	free(aux->key_pair);
	aux->key_pair = create_keypair(name, value);
}