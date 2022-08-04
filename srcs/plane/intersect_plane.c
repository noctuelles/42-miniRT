/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:17:47 by bsavinel          #+#    #+#             */
/*   Updated: 2022/07/30 14:35:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "math_utils.h"
#include "tuple.h"
#include "matrix.h"

/*bool	plane_intersection(t_object *object, t_ray *ray, t_rayhit *rayhit)
{
	rayhit->normal = object->p.plan.normal;
	rayhit->t = vec_dot(object->p.plan.normal,
			tsub(object->p.plan.pos, ray->org))
		/ vec_dot(object->p.plan.normal, ray->dir);
	rayhit->intersect_p = tadd(ray->org, tmul_scalar(ray->dir,
				rayhit->t));;
	rayhit->intersect_p_local = rayhit->intersect_p;
	if (rayhit->t >= 0)
		return (true);
	else
		return (false);
}*/

bool	plane_intersection(t_object *object, t_ray *ray, t_rayhit *rayhit)
{
	t_ray	new_ray;

	new_ray = ray_transform(*ray, object->M_inv);
	rayhit->t = -new_ray.org.y / new_ray.dir.y;
	if (rayhit->t < 0)
		return (false);
	rayhit->intersect_p = get_ray_point(*ray, rayhit->t);
	rayhit->intersect_p_local = get_ray_point(new_ray, rayhit->t);
	rayhit->normal = object->p.plan.normal;
	return (true);
}
