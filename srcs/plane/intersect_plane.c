/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:17:47 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/16 17:38:03 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "vector.h"

bool	plane_intersection(t_object *object, t_ray *ray)
{
	if (vec_dot(object->p.plan.normal, ray->dir) == 0)
		return (false);
	object->rayhit.normal = object->p.plan.normal;
	object->rayhit.t = vec_dot(object->p.plan.normal,
			vec_sub(object->p.plan.point, ray->org))
		/ vec_dot(object->p.plan.normal, ray->dir);
	object->rayhit.intersect_p = vec_add(ray->org, vec_mul_scalar(ray->dir,
				object->rayhit.t));
	if (object->rayhit.t > 0)
		return (true);
	else
		return (false);
}
