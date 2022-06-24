/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:54:03 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/24 17:00:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Column-major convetion is used here. */

/* Multiply two 4x4 matrixs (column-major) and return the result. */

t_matrix4	matrix4_mul(t_matrix4 const A, t_matrix4 const B)
{
	t_matrix4	M;
	uint8_t		i;
	uint8_t		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			M.m[i][j] = A.m[i][0] * B.m[0][j] +
					A.m[i][1] * B.m[1][j] +
					A.m[i][2] * B.m[2][j] +
					A.m[i][3] * B.m[3][j];
			j++;
		}
		i++;
	}
	return (M);
}

/* Multiply matrix A with the identity matrix. */

t_matrix4	matrix4_mul_id(t_matrix4 const A)
{
	t_matrix4	id;
	uint8_t		i;
	uint8_t		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				id.m[i][j] = 1.;
			else
				id.m[i][j] = 0.;
			j++;
		}
		i++;
	}
	return (matrix4_mul(A, id));
}



/* Transpose a 4x4 matrix.
 * Turn rows into columns and vise-versa.*/

t_matrix4	matrix4_trans(t_matrix4 const A)
{
	t_matrix4	M;
	uint8_t		i;
	uint8_t		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			M.m[i][j] = A.m[j][i];
			j++;
		}
		i++;
	}
	return (M);
}

/* Multiply a tuple by a 4x4 matrix. Return the transformed tuple. */

t_tuple	matrix4_tmul(t_matrix4 const A, t_tuple B)
{
	t_tuple	t;

	t.x = A.m[0][0] * B.x + A.m[0][1] * B.y + A.m[0][2] * B.z
		+ A.m[0][3] * B.w;
	t.y = A.m[1][0] * B.x + A.m[1][1] * B.y + A.m[1][2] * B.z
		+ A.m[1][3] * B.w;
	t.z = A.m[2][0] * B.x + A.m[2][1] * B.y + A.m[2][2] * B.z
		+ A.m[2][3] * B.w;
	t.w = A.m[3][0] * B.x + A.m[3][1] * B.y + A.m[3][2] * B.z
		+ A.m[3][3] * B.w;
	return (t);
}
