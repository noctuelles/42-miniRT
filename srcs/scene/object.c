/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:43:00 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 18:12:22 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "ray_intersection.h"
#include "mlx_utils.h"
#include "matrix.h"
#include "tuple.h"
#include <stdlib.h>
#include <stdio.h>

t_object	*new_sphere(t_point3 pos, double radius, uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.sphere.pos = pos;
	obj->p.sphere.radius = radius;
	obj->fnct = &intersect_sphere;
	obj->type = T_SPHERE;
	obj->albedo = get_norm_color(color);
	obj->M = matrix4_mul(matrix4_translate(pos.x, pos.y, pos.z),
			matrix4_scale(radius, radius, radius));
	obj->M_inv = matrix4_inv(obj->M);
	obj->M_inv_trans = matrix4_trans(obj->M_inv);
	return (obj);
}

t_object	*new_plan(t_point3 pos, t_vec3 normal, uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.plan.pos = pos;
	obj->p.plan.normal = normal;
	obj->fnct = &plane_intersection;
	obj->type = T_PLAN;
	obj->albedo = get_norm_color(color);
	return (obj);
}

t_object	*new_cylindre(t_point3 center, t_vec3 orientation, double rayon, double hauteur, uint32_t color)
{
	t_object	*obj;
	uint8_t	r, g, b;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.cylindre.orientation = orientation;
	obj->p.cylindre.center = center;
	obj->p.cylindre.hauteur = hauteur;
	obj->p.cylindre.rayon = rayon;
	obj->fnct = &intersect_cylindre;
	obj->type = T_CYLINDRE;
	r = color >> 16;
	g = color >> 8;
	b = 0xFF & color;
	obj->M = matrix4_translate(center.x, center.y, center.z);
	obj->M_inv = matrix4_inv(obj->M);
	obj->albedo = get_norm_color(color);
	return (obj);
}

t_object	*new_cone(t_point3 top, t_vec3 direction, double angle, double hauteur, uint32_t color)
{
	t_object	*obj;
	uint8_t	r, g, b;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.cone.top = top;
	obj->p.cone.direction = direction;
	obj->p.cone.angle = angle;
	obj->p.cone.hauteur = hauteur;
	obj->fnct = &intersect_cone;
	obj->type = T_CYLINDRE;
	r = color >> 16;
	g = color >> 8;
	b = 0xFF & color;
	obj->albedo = get_norm_color(color);
	return (obj);
}

void	apply_obj_transform(t_object *obj, t_matrix4 const M)
{
	obj->M = M;
	obj->M_inv = matrix4_inv(M);
}
