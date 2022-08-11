/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:59:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/11 17:14:30 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "math_utils.h"
#include "tuple.h"
#include <math.h>
#include <stdio.h>
#include "matrix.h"

/* Edge cases :
 *
 *     - If the ray hits in negative t values (if the second intersection is 
 *     negative then the sphere is begind the sphere origin.)
*/

static inline t_vec3	compute_normal(t_object *obj, t_point3 t)
{
	t_vec3	world_normal;

	world_normal = vec_norm(matrix4_tmul(obj->m_inv_trans, t));
	world_normal.w = 0;
	return (world_normal);
}

bool	intersect_sphere(t_object *obj, t_ray *ray, t_rayhit *rayhit)
{
	t_vec3	sphere_to_ray;
	t_ray	local_ray;
	double	t[2];

	local_ray = ray_transform(*ray, obj->m_inv);
	sphere_to_ray = tsub(local_ray.org, point(0., 0., 0.));
	if (solve_quadratic(
			vec_dot(local_ray.dir, local_ray.dir),
			2 * vec_dot(local_ray.dir, sphere_to_ray),
			vec_dot(sphere_to_ray, sphere_to_ray) - 1,
			t))
	{
		if (t[1] < 0)
			return (false);
		if (t[0] < 0)
			rayhit->t = t[1];
		else
			rayhit->t = t[0];
		rayhit->intersect_p = get_ray_point(*ray, rayhit->t);
		rayhit->intersect_p_local = get_ray_point(local_ray, rayhit->t);
		rayhit->normal = compute_normal(obj, rayhit->intersect_p_local);
		return (true);
	}
	return (false);
}
