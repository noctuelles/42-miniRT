/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:43:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/04 20:16:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "matrix.h"
#include "tuple.h"
#include "math_utils.h"
#include <stdbool.h>
#include <math.h>

double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

/* Solve a given quadratic equation with the given parameter. */

bool	solve_quadratic(double a, double b, double c, double t[2])
{
	double	discriminant;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (false);
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	return (true);
}

/* Transform a given ray with a given matrix. */

t_ray	ray_transform(t_ray old_ray, t_matrix4 const M)
{
	t_ray	new_ray;

	new_ray.org = matrix4_tmul(M, old_ray.org);
	new_ray.dir = matrix4_tmul(M, old_ray.dir);
	return (new_ray);
}

t_point3	get_ray_point(t_ray ray, double t)
{
	return (tadd(ray.org, tmul_scalar(ray.dir, t)));
}


t_vec3		get_normal(t_object *obj, t_point3 p)
{
	t_vec3	obj_normal;
	t_vec3	world_normal;

	obj_normal = matrix4_tmul(obj->M_inv, p);
	world_normal = matrix4_tmul(obj->M_inv_trans, obj_normal);
	return (vec_norm(world_normal));
}

t_vec3	get_reflection_vec(t_vec3 incident, t_vec3 normal)
{
	t_vec3	reflectionv;

	reflectionv = tsub(tmul_scalar(normal, 2 * vec_dot(incident, normal)), incident);
	return (reflectionv);
}
