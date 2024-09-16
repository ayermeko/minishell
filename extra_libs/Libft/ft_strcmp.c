/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermko@student.42prague.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:37:19 by ayermeko          #+#    #+#             */
/*   Updated: 2023/11/18 18:37:22 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] == b[i] && a[i] != '\0' && b[i] != '\0')
	{
		i++;
	}
	return (a[i] - b[i]);
}
