/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:29:32 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 14:59:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "minirt_lexer.h"
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

/* check_file_extension() check if filename is a file with the
 * .rt extension. */

static bool	check_file_extension(const char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot)
		return (false);
	if (ft_strcmp(dot, STR_FILE_EXTENSION) != 0)
		return (false);
	else
		return (true);
}

static char	**fill_file(int fd, size_t nbr_lines)
{
	char	**file;
	size_t	i;
	size_t	n;

	i = 0;
	file = malloc((nbr_lines + 1) * sizeof(char *));
	if (!file)
		return (NULL);
	while (readline(fd, &file[i]))
	{
		if (file[i][0] == '\n' && file[i][1] == '\0')
			free(file[i]);
		else
			i++;
	}
	if (file[i] == NULL && errno)
	{
		n = 0;
		while (n < i)
			free(file[n++]);
		free(file);
		file = NULL;
	}
	close(fd);
	return (file);
}

char	**read_file(const char *filename)
{
	char	**file;
	size_t	nbr_lines;
	int		fd;

	errno = 0;
	if (check_file_extension(filename) == false)
		return (print_error(STR_INVALID_FILE_EXTENSION));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error_function(STR_FUNCTION_OPEN));
	nbr_lines = get_file_nbr_lines(fd);
	if (nbr_lines == 0)
	{
		if (errno)
			return (print_error_function(STR_FUNCTION_READ));
		else
			return (print_error(STR_EMPTY_FILE));
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error_function(STR_FUNCTION_OPEN));
	file = fill_file(fd, nbr_lines);
	if (!file)
		return (print_error_function(STR_ERROR_FILE_READ));
	return (file);
}
