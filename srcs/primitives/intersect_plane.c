/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:17:47 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 17:15:41 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "math_utils.h"
#include "tuple.h"
#include "matrix.h"
#include <math.h>

bool	plane_intersection(t_object *object, t_ray *ray, t_rayhit *rayhit)
{
	t_ray	new_ray;

	new_ray = ray_transform(*ray, object->m_inv);
	if (fequals(new_ray.dir.y, 0))
		return (false);
	rayhit->t = -new_ray.org.y / new_ray.dir.y;
	if (rayhit->t < 0)
		return (false);
	rayhit->intersect_p = get_ray_point(*ray, rayhit->t);
	rayhit->intersect_p_local = get_ray_point(new_ray, rayhit->t);
	rayhit->normal = vec_norm(matrix4_tmul(object->m_inv_trans,
				vector(0, 1, 0)));
	rayhit->normal.w = 0;
	return (true);
}
