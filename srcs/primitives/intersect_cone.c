/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:37:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/10 13:23:41 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "math_utils.h"
#include "tuple.h"
#include "matrix.h"
#include "define.h"
#include <math.h>

static inline t_vec3	compute_normal(t_object *obj, t_point3 t)
{
	t_vec3	obj_normal;
	t_vec3	world_normal;
	double	radius;

	radius = sqr(t.x) + sqr(t.z);
	if (radius < 1 && t.y <= -1 + EPSILON)
		obj_normal = vector(0, -1, 0);
	else
		obj_normal = vector(t.x, sqrt(radius), t.z);
	world_normal = vec_norm(matrix4_tmul(obj->M_inv_trans, obj_normal));
	world_normal.w = 0;
	return (world_normal);
}

/* Check if the intersection point is within the radius of the cone. */

static inline bool	check_end_cap(t_ray ray, double t)
{
	double	x;
	double	z;
	double	radius;

	x = ray.org.x + ray.dir.x * t;
	z = ray.org.z + ray.dir.z * t;
	radius = x * x + z * z;
	if (radius <= 1)
		return (true);
	else
		return (false);
}

static inline void	intersect_cone_body(t_ray lray, double *body_t)
{
	double	t[2];
	double	valid_t[2];
	double	y[2];

	valid_t[0] = INFINITY;
	valid_t[1] = INFINITY;
	if (solve_quadratic(
			sqr(lray.dir.x) - sqr(lray.dir.y) + sqr(lray.dir.z),
			2 * lray.org.x * lray.dir.x - 2 * lray.org.y * lray.dir.y
			+ 2 * lray.org.z * lray.dir.z,
			sqr(lray.org.x) - sqr(lray.org.y) + sqr(lray.org.z), t))
	{
		if (t[1] < 0)
			return ;
		y[0] = lray.org.y + lray.dir.y * t[0];
		y[1] = lray.org.y + lray.dir.y * t[1];
		if (y[0] > -1 && y[0] < 0)
			valid_t[0] = t[0];
		if (y[1] > -1 && y[1] < 0)
			valid_t[1] = t[1];
		if (valid_t[0] < valid_t[1] && valid_t[0] > 0)
			*body_t = valid_t[0];
		else
			*body_t = valid_t[1];
	}
}

static inline void	intersect_cone_endcap(t_ray lray, double *endcap_t)
{
	double	t;

	t = INFINITY;
	t = (-1 - lray.org.y) / lray.dir.y;
	if (t > 0 && check_end_cap(lray, t))
		*endcap_t = t;
}

bool	intersect_cone(t_object *obj, t_ray *ray, t_rayhit *rayhit)
{
	t_ray	lray;
	double	cone_t[2];

	cone_t[0] = INFINITY;
	cone_t[1] = INFINITY;
	lray = ray_transform(*ray, obj->M_inv);
	intersect_cone_body(lray, &cone_t[0]);
	intersect_cone_endcap(lray, &cone_t[1]);
	rayhit->t = min(cone_t[0], cone_t[1]);
	if (rayhit->t == INFINITY)
		return (false);
	rayhit->intersect_p = get_ray_point(*ray, rayhit->t);
	rayhit->intersect_p_local = get_ray_point(lray, rayhit->t);
	rayhit->normal = compute_normal(obj, rayhit->intersect_p_local);
	return (true);
}
