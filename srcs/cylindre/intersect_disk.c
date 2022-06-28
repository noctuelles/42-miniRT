/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_disk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:25:34 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/25 15:08:38 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "tuple.h"

bool	intersect_disk(t_object *obj, t_ray *ray)
{
	if (vec_dot(obj->p.disk.normal, ray->dir) == 0)
		return (false);
	obj->rayhit.normal = obj->p.disk.normal;
	obj->rayhit.t = vec_dot(obj->p.disk.normal,
			tsub(obj->p.disk.center, ray->org))
		/ vec_dot(obj->p.disk.normal, ray->dir);
	obj->rayhit.intersect_p = tadd(ray->org,
			tmul_scalar(ray->dir, obj->rayhit.t));
	if (obj->rayhit.t > 0 && vec_mag(tsub(obj->p.disk.center,
				obj->rayhit.intersect_p)) <= obj->p.disk.rayon)
		return (true);
	return (false);
}
