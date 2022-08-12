/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invert_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:09:39 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 16:09:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdint.h>

static t_matrix2	matrix3_submatrix(t_matrix3 const A, uint8_t row,
		uint8_t column)
{
	t_matrix2	m;
	uint8_t		i;
	uint8_t		j;
	uint8_t		k;
	uint8_t		l;

	i = 0;
	k = 0;
	while (i < 3)
	{
		j = 0;
		l = 0;
		if (i != row)
		{
			while (j < 3)
			{
				if (j != column)
					m.m[k][l++] = A.m[i][j];
				j++;
			}
			k++;
		}
		i++;
	}
	return (m);
}

static inline double	matrix2_determinant(t_matrix2 const A)
{
	return (A.m[0][0] * A.m[1][1] - A.m[0][1] * A.m[1][0]);
}

static inline double	matrix3_minor(t_matrix3 const A, uint8_t row,
		uint8_t column)
{
	return (matrix2_determinant(matrix3_submatrix(A, row, column)));
}

static inline double	matrix3_cofactor(t_matrix3 const A, uint8_t row,
		uint8_t column)
{
	double	minor;

	minor = matrix3_minor(A, row, column);
	if ((row + column) % 2 != 0)
		return (-minor);
	else
		return (minor);
}

double	matrix3_determinant(t_matrix3 const A)
{
	uint8_t	j;
	double	det;

	j = 0;
	det = 0.;
	while (j < 3)
	{
		det += A.m[0][j] * matrix3_cofactor(A, 0, j);
		j++;
	}
	return (det);
}
