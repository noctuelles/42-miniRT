/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:58:52 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/27 16:03:27 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "define.h"
#include "math_utils.h"
#include <math.h>
#include "tuple.h"

bool	give_intersect_cone(t_object *obj, t_ray *ray, double distance[2])
{
	double	a;
	double	b;
	double	c;
	t_tuple	top_org;
	double	cos_square;

	top_org = tsub(ray->org, obj->p.cone.top);
	cos_square = pow(cos((obj->p.cone.angle * M_PI) / 180), 2);
	a = pow(vec_dot(ray->dir, obj->p.cone.dir), 2) - cos_square;
	b = 2 * (vec_dot(ray->dir, obj->p.cone.dir)
			* vec_dot(top_org, obj->p.cone.dir)
			- vec_dot(ray->dir, tmul_scalar(top_org, cos_square)));
	c = pow(vec_dot(top_org, obj->p.cone.dir), 2)
		- vec_dot(top_org, tmul_scalar(top_org, cos_square));
	return (solve_quadratic(a, b, c, distance));
}

t_vec3	find_normal_cone(t_object *obj, t_rayhit rayhit, t_ray *ray)
{
	double		distance;
	t_point3	point;

	distance = vec_mag(tsub(obj->p.cone.top, rayhit.intersect_p));
	point = tadd(obj->p.cone.top, tmul_scalar(obj->p.cone.dir, distance));
	return (vec_norm(tsub(rayhit.intersect_p, point)));
}
