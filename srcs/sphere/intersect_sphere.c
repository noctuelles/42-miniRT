/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:59:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/16 16:56:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

bool	intersect_sphere(t_object *obj, t_ray *ray)
{
	t_3dpoint	p;
	double		solution[2];
	double		eq_xy[2];
	double		t;

	t = vec_dot(vec_sub(obj->p.sphere.center, ray->org), ray->dir);
	p = vec_add(ray->org, vec_mul_scalar(ray->dir, t));
	eq_xy[1] = vec_length(vec_sub(obj->p.sphere.center, p));
	eq_xy[0] = sqrt(obj->p.sphere.radius * obj->p.sphere.radius
			- eq_xy[1] * eq_xy[1]);
	if (eq_xy[1] < obj->p.sphere.radius)
	{
		solution[0] = t - eq_xy[0];
		solution[1] = t + eq_xy[1];
		obj->rayhit.t = solution[0];
		obj->rayhit.intersect_p = vec_add(ray->org, vec_mul_scalar(ray->dir,
					solution[0]));
		obj->rayhit.normal = vec_normalize(vec_sub(obj->rayhit.intersect_p,
					obj->p.sphere.center)); 
		return (true);
	}
	else
		return (false);
}
