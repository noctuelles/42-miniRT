/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:50:45 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/06 18:16:16 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuple.h"
#include <math.h>

t_matrix4	build_view_transform(t_vec3 forward, t_point3 from)
{
	t_matrix4	M;
	t_vec3		xaxis;
	t_vec3		yaxis;
	t_vec3		up;

	up = point(0, 1, 0);
	forward = vec_norm(forward);
	xaxis = vec_norm(vec_cross(up, forward));
	yaxis = vec_norm(vec_cross(forward, xaxis));
	M.m[0][0] = xaxis.x;
	M.m[1][0] = yaxis.x;
	M.m[2][0] = forward.x;

	M.m[0][1] = xaxis.y;
	M.m[1][1] = yaxis.y;
	M.m[2][1] = forward.y;

	M.m[0][2] = xaxis.z;
	M.m[1][2] = yaxis.z;
	M.m[2][2] = forward.z;

	M.m[3][3] = 1.;
	return (matrix4_mul(M, matrix4_translate(-from.x, -from.y, -from.z)));
}

t_camera new_camera(size_t hsize, size_t vsize, double fov)
{
	t_camera	camera;
	double		aspect;
	double		half_view;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.fov = fov;
	aspect = (float) hsize / vsize;
	half_view = tan(fov / 2);
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / hsize;
	return (camera);
}

t_ray	generate_ray(t_camera *camera, size_t i, size_t j)
{
}
