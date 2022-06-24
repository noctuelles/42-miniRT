/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:06:22 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/24 18:32:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include <stdio.h>

/* Display a 4x4 matrix. */

void	print_matrix4(t_matrix4 const M)
{
	uint8_t	i;
	uint8_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		printf("{");
		while (j < 4)
		{
			printf("%10.5f", M.m[i][j]);
			if (j != 3)
				printf(", ");
			j++;
		}
		printf("}\n");
		i++;
	}
}

void	print_matrix3(t_matrix3 const M)
{
	uint8_t	i;
	uint8_t	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		printf("{");
		while (j < 3)
		{
			printf("%10.2f", M.m[i][j]);
			if (j != 2)
				printf(", ");
			j++;
		}
		printf("}\n");
		i++;
	}
}

void	print_matrix2(t_matrix2 const M)
{
	uint8_t	i;
	uint8_t	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		printf("{");
		while (j < 2)
		{
			printf("%10.2f", M.m[i][j]);
			if (j != 1)
				printf(", ");
			j++;
		}
		printf("}\n");
		i++;
	}
}
