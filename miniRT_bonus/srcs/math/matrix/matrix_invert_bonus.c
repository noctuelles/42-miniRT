/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:25:15 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 16:09:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_bonus.h"
#include <stdint.h>

static t_matrix3	matrix4_submatrix(t_matrix4 const A, uint8_t row,
		uint8_t column)
{
	t_matrix3	m;
	uint8_t		i;
	uint8_t		j;
	uint8_t		k;
	uint8_t		l;

	i = 0;
	k = 0;
	while (i < 4)
	{
		j = 0;
		l = 0;
		if (i != row)
		{
			while (j < 4)
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

static inline double	matrix4_minor(t_matrix4 const A, uint8_t row,
		uint8_t column)
{
	return (matrix3_determinant(matrix4_submatrix(A, row, column)));
}

static inline double	matrix4_cofactor(t_matrix4 const A, uint8_t row,
		uint8_t column)
{
	double	minor;

	minor = matrix4_minor(A, row, column);
	if ((row + column) % 2 != 0)
		return (-minor);
	else
		return (minor);
}

static inline double	matrix4_determinant(t_matrix4 const A)
{
	uint8_t	j;
	double	det;

	j = 0;
	det = 0.;
	while (j < 4)
	{
		det += A.m[0][j] * matrix4_cofactor(A, 0, j);
		j++;
	}
	return (det);
}

t_matrix4	matrix4_inv(t_matrix4 const A)
{
	t_matrix4	m;
	double		c;
	double		d;
	uint8_t		i;
	uint8_t		j;

	m = A;
	i = 0;
	d = matrix4_determinant(A);
	if (d == 0)
		return (A);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			c = matrix4_cofactor(A, i, j);
			m.m[j][i] = c / d;
			j++;
		}
		i++;
	}
	return (m);
}
