/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:27:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/08 17:33:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static ssize_t	read_fd(int fd, char *buffer, ssize_t *rdead, size_t index)
{
	if (index == 0)
		*rdead = read(fd, buffer, 4096);
	return (*rdead);
}

/* Instead of using get_next_line to count line, i use a dedicated fonction,
 * Which is more efficient (no malloc..).*/

size_t	get_file_nbr_lines(int fd)
{
	size_t	i;
	size_t	nbr_lines;
	ssize_t	rdead;
	char	buffer[4096];

	i = 0;
	nbr_lines = 0;
	ft_memset(&buffer, 0, 4096);
	while (read_fd(fd, buffer, &rdead, i) > 0)
	{
		while (i < (size_t)(rdead - 1) && buffer[i] != '\n')
			i++;
		if (buffer[i++] == '\n')
		{
			while (buffer[i] == '\n')
				i++;
			nbr_lines++;
		}
		else
			i = 0;
	}
	if (rdead == -1)
		return (0);
	close(fd);
	return (nbr_lines);
}
