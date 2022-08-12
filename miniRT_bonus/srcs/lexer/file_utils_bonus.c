/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:27:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 13:26:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*readline(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line);
}

size_t	get_file_nbr_lines(int fd)
{
	size_t	nbr_lines;
	char	*line;

	nbr_lines = 0;
	while (readline(fd, &line))
	{
		free(line);
		nbr_lines++;
	}
	close(fd);
	return (nbr_lines);
}
