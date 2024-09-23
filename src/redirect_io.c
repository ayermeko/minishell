/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:27:34 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/23 21:52:45 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	save_original_fd_in(int original_fds[2], int fd_index)
{
	if (original_fds[fd_index] == NO_REDIRECT)
		original_fds[fd_index] = dup(fd_index);
}

int	redirect_input(char *input)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;

	input_redirect = get_spos(input, "<");
	if (!*input_redirect)
		return (SUCCESS);
	file_name = get_delimiter(input_redirect);
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("filename does not accessible.", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, 0);
	free(file_name);
	return (SUCCESS);
}

int	handle_input(char *input, int original_fds[2])
{
	save_original_fd_in(original_fds, 0);
	if (redirect_input(input) == FAILED)
	{
		redirect_fd(original_fds[0], 0);
		return (FAILED);
	}
	return (SUCCESS);
}


int	redirect_output(char *command)
{
	char	*output_redirect;
	char	*file_name;
	int		fd;
	int		open_flags;

	output_redirect = get_redirect_position(command, '>');
	if (!*output_redirect)
		return (SUCCESS);
	if (output_redirect[1] == '>')
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	file_name = get_delimiter(output_redirect);
	fd = open(file_name, open_flags, 0644);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, 1);
	free(file_name);
	return (SUCCESS);
}

int	handle_output(char *command, int original_fds[2])
{
	save_original_fd_out(original_fds, 1);
	if (redirect_output(command) == FAILED)
	{
		redirect_fd(original_fds[1], 1);
		return (FAILED);
	}
	return (SUCCESS);
}