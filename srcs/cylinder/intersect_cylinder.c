/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:41:15 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/05 11:20:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "math_utils.h"
#include "tuple.h"
#include "matrix.h"
#include "define.h"
#include <math.h>

/* Compute the cylinder normal.
 * It detects if the intersection point is on one of the endcaps or the body,
 * and set the object normal vector accordingly. */

static inline t_vec3 compute_normal(t_object *obj, t_point3 t)
{
	t_vec3	obj_normal;
	t_vec3	world_normal;
	double	radius;

	radius = t.x * t.x + t.z * t.z;
	if (radius < 1 && t.y >= obj->p.cylinder.half_height - EPSILON)
		obj_normal = vector(0, 1, 0);
	else if (radius < 1 && t.y <= -obj->p.cylinder.half_height + EPSILON)
		obj_normal = vector(0, -1, 0);
	else
		obj_normal = vector(t.x, 0, t.z);
	world_normal = vec_norm(matrix4_tmul(obj->M_inv_trans, obj_normal));
	world_normal.w = 0;
	return (world_normal);
}

/* Check if the intersection point is within the radius of the cylinder. */

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

static inline void
		intersect_cylinder_endcap(t_ray lray, double halfh, double *endcap_t)
{
	double	t[2];
	double	inter_t[2];

	inter_t[0] = INFINITY;
	inter_t[1] = INFINITY;
	t[0] = (-halfh - lray.org.y) / lray.dir.y;
	t[1] = (halfh - lray.org.y) / lray.dir.y;
	if (t[0] > 0 && check_end_cap(lray, t[0]))
		inter_t[0] = t[0];
	if (t[1] > 0 && check_end_cap(lray, t[1]))
		inter_t[1] = t[1];
	*endcap_t = min(inter_t[0], inter_t[1]);
}

static inline void
			intersect_cylinder_body(t_ray lray, double halfh, double *body_t)
{
	double	t[2];
	double	valid_t[2];
	double	y[2];

	valid_t[0] = INFINITY;
	valid_t[1] = INFINITY;
	if (solve_quadratic(
				lray.dir.x * lray.dir.x + lray.dir.z * lray.dir.z,
				2 * (lray.org.x * lray.dir.x) + 2 * (lray.org.z * lray.dir.z),
				(lray.org.x * lray.org.x) + (lray.org.z * lray.org.z) - 1, t))
	{
		if (t[1] < 0)
			return ;
		y[0] = lray.org.y + lray.dir.y * t[0]; 
		y[1] = lray.org.y + lray.dir.y * t[1]; 
		if (y[0] > -halfh && y[0] < halfh)
			valid_t[0] = t[0];
		if (y[1] > -halfh && y[1] < halfh)
			valid_t[1] = t[1];
		if (valid_t[0] < valid_t[1] && valid_t[0] > 0)
			*body_t = valid_t[0];
		else
			*body_t = valid_t[1];
	}
}

bool	intersect_cylinder(t_object *obj, t_ray *ray, t_rayhit *rayhit)
{
	t_ray	lray;
	double	cyl_t[2];

	cyl_t[0] = INFINITY;
	cyl_t[1] = INFINITY;
	lray = ray_transform(*ray, obj->M_inv);

	intersect_cylinder_body(lray, obj->p.cylinder.half_height, &cyl_t[0]);
	intersect_cylinder_endcap(lray, obj->p.cylinder.half_height, &cyl_t[1]);

	rayhit->t = min(cyl_t[0], cyl_t[1]);
	if (rayhit->t == INFINITY)
		return (false);
	rayhit->intersect_p = get_ray_point(*ray, rayhit->t);
	rayhit->intersect_p_local = get_ray_point(lray, rayhit->t);
	rayhit->normal = compute_normal(obj, rayhit->intersect_p_local);
	return (true);
}
