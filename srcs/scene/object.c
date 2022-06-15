/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:43:00 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/15 19:36:54 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "ray_intersection.h"
#include <stdlib.h>

t_object	*new_sphere(t_3dpoint center, double radius, uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.sphere.center = center;
	obj->p.sphere.radius = radius;
	obj->fnct = &intersect_sphere;
	obj->type = T_SPHERE;
	obj->color = color;
	return (obj);
}

t_object	*new_plan(t_3dpoint point, t_vec3d normal, uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.plan.point = point;
	obj->p.plan.normal = normal;
	obj->fnct = &intersect_sphere;
	obj->type = T_PLAN;
	obj->color = color;
	return (obj);
}
