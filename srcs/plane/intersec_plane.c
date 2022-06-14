/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:17:47 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/14 18:12:15 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "vector.h"

int ray_intersec_plane_front(double t,t_vec3d normal, t_vec3d ray )
{
	if (t < 0 || vec_dot(normal, ray) == 0)
		return (0);
	return (0);
}

t_3dpoint	point_intersection(double t, t_3dpoint eye, t_vec3d ray)
{
	return (vec_add(eye, vec_mul_scalar(ray, t)));
}

int plane_intersection(t_3dpoint point, t_vec3d normal, t_3dpoint eye, t_vec3d ray)
{
	double t;

	t = vec_dot(normal, vec_sub(point, eye)) / vec_dot(normal, ray);
	if (ray_intersec_plane_front(t, normal, ray))
		return (1);
	return (0);
}