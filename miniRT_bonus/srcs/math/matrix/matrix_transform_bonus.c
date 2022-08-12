/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:57:18 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 16:43:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_bonus.h"
#include "libft.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

/* Build a translation matrix. */

t_matrix4	matrix4_translate(double x, double y, double z)
{
	t_matrix4	m;

	ft_memset(&m, 0, sizeof(t_matrix4));
	m.m[0][0] = 1.;
	m.m[1][1] = 1.;
	m.m[2][2] = 1.;
	m.m[3][3] = 1.;
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

/* Build a scaling matrix. */

t_matrix4	matrix4_scale(double x, double y, double z)
{
	t_matrix4	m;

	ft_memset(&m, 0, sizeof(t_matrix4));
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	m.m[3][3] = 1.;
	return (m);
}

/* Build a rotation matrix to move a tuple around the x axis. */

t_matrix4	matrix4_rotate_x(double r)
{
	t_matrix4	m;

	ft_memset(&m, 0, sizeof(t_matrix4));
	m.m[0][0] = 1.;
	m.m[3][3] = 1.;
	m.m[1][1] = cos(r);
	m.m[1][2] = -sin(r);
	m.m[2][1] = sin(r);
	m.m[2][2] = cos(r);
	return (m);
}

/* Build a rotation matrix to move a tuple around the y axis. */

t_matrix4	matrix4_rotate_y(double r)
{
	t_matrix4	m;

	ft_memset(&m, 0, sizeof(t_matrix4));
	m.m[1][1] = 1.;
	m.m[3][3] = 1.;
	m.m[0][0] = cos(r);
	m.m[0][2] = sin(r);
	m.m[2][0] = -sin(r);
	m.m[2][2] = cos(r);
	return (m);
}

/* Build a rotation matrix to move a tuple around the z axis. */

t_matrix4	matrix4_rotate_z(double r)
{
	t_matrix4	m;

	ft_memset(&m, 0, sizeof(t_matrix4));
	m.m[2][2] = 1.;
	m.m[3][3] = 1.;
	m.m[0][0] = cos(r);
	m.m[0][1] = -sin(r);
	m.m[1][0] = sin(r);
	m.m[1][1] = cos(r);
	return (m);
}

/*
t_matrix4	matrix4_shear(double xy, double xz, double yx, double yz,
		double zx, double zy)
{
	t_matrix4	M;

	ft_memset(&M, 0, sizeof(t_matrix4));
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
