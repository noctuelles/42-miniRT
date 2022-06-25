/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:59:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 04:31:18 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "math_utils.h"
#include "tuple.h"
#include <math.h>
#include <stdio.h>

/* Edge cases :
 *
 *     - If the ray hits in negative t values (if the second intersection is 
 *     negative then the sphere is begind the sphere origin.)
*/

bool	intersect_sphere(t_object *obj, t_ray *ray, t_rayhit *rayhit)
{
	t_vec3	sphere_to_ray;
	t_ray	new_ray;
	double	t[2];

	new_ray = ray_transform(*ray, obj->M_inv);
	sphere_to_ray = tsub(new_ray.org, point(0., 0., 0.));
	if (solve_quadratic(
				vec_dot(new_ray.dir, new_ray.dir),
				2 * vec_dot(new_ray.dir, sphere_to_ray),
				vec_dot(sphere_to_ray, sphere_to_ray) - 1,
				t))
	{
		if (t[1] < 0)
			return (false);
		t[0] = min(t[0], t[1]);
		rayhit->t = t[0];
		rayhit->intersect_p = get_ray_point(*ray, t[0]);
		rayhit->normal = vec_norm(get_ray_point(new_ray, t[0]));
		return (true);
	}
	return (false);
}
