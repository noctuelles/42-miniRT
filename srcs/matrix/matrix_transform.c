/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:57:18 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/24 18:37:26 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

/* Build a translation matrix. */

t_matrix4	matrix4_translate(double x, double y, double z)
{
	t_matrix4	M;

	memset(&M, 0, sizeof(t_matrix4));
	M.m[0][0] = 1.;
	M.m[1][1] = 1.;
	M.m[2][2] = 1.;
	M.m[3][3] = 1.;
	M.m[0][3] = x;
	M.m[1][3] = y;
	M.m[2][3] = z;
	return(M);
}

/* Build a scaling matrix. */

t_matrix4	matrix4_scale(double x, double y, double z)
{
	t_matrix4	M;

	memset(&M, 0, sizeof(t_matrix4));
	M.m[0][0] = x;
	M.m[1][1] = y;
	M.m[2][2] = z;
	M.m[3][3] = 1.;
	return (M);
}

/* Build a rotation matrix to move a tuple around the x axis. */

t_matrix4	matrix4_rotate_x(double r)
{
	t_matrix4	M;

	memset(&M, 0, sizeof(t_matrix4));
	M.m[0][0] = 1.;
	M.m[3][3] = 1.;
	M.m[1][1] = cos(r);
	M.m[1][2] = -sin(r);
	M.m[2][1] = sin(r);
	M.m[2][2] = cos(r);
	return (M);
}

/* Build a rotation matrix to move a tuple around the y axis. */

t_matrix4	matrix4_rotate_y(double r)
{
	t_matrix4	M;

	memset(&M, 0, sizeof(t_matrix4));
	M.m[1][1] = 1.;
	M.m[3][3] = 1.;
	M.m[0][0] = cos(r);
	M.m[0][2] = sin(r);
	M.m[2][0] = -sin(r);
	M.m[2][2] = cos(r);
	return (M);
}

/* Build a rotation matrix to move a tuple around the z axis. */

t_matrix4	matrix4_rotate_z(double r)
{
	t_matrix4	M;

	memset(&M, 0, sizeof(t_matrix4));
	M.m[2][2] = 1.;
	M.m[3][3] = 1.;
	M.m[0][0] = cos(r);
	M.m[0][1] = -sin(r);
	M.m[1][0] = sin(r);
	M.m[1][1] = cos(r);
	return (M);
}

/*
t_matrix4	matrix4_shear(double xy, double xz, double yx, double yz,
		double zx, double zy)
{
	t_matrix4	M;

	memset(&M, 0, sizeof(t_matrix4));
	M.m[0][0] = 1.;
	M.m[1][1] = 1;
	M.m[2][2] = 1;
	M.m[3][3] = 1;
	M.m[0][1] = xy;
	M.m[0][2] = xz;
	M.m[1][0] = yx;
	M.m[1][2] = yz;
	M.m[2][0] = zx;
	M.m[2][1] = zy;
	return (M);
}*/
