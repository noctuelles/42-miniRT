/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:43:00 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/11 18:15:20 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "ray_intersection_bonus.h"
#include "mlx_utils_bonus.h"
#include "texture_bonus.h"
#include "define_bonus.h"
#include "matrix_bonus.h"
#include "tuple_bonus.h"
#include "scene_bonus.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

t_object	*new_cylinder(t_point3 pos, double diam_heig[2], t_vec3 orient,
		uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = O_CYLINDER;
	obj->albedo = get_norm_color(color);
	obj->fnct = &intersect_cylinder;
	obj->uvmap_fnct = &get_cylinder_map;
	obj->m = matrix4_scale(diam_heig[0], diam_heig[1], diam_heig[0]);
	obj->m = matrix4_mul(build_rotation_matrix(vec_norm(orient)), obj->m);
	obj->m = matrix4_mul(matrix4_translate(pos.x, pos.y, pos.z), obj->m);
	obj->m_inv = matrix4_inv(obj->m);
	obj->m_inv_trans = matrix4_trans(obj->m_inv);
	return (obj);
}

t_object	*new_sphere(t_point3 pos, double radius, uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = O_SPHERE;
	obj->fnct = &intersect_sphere;
	obj->uvmap_fnct = &get_spherical_map;
	obj->albedo = get_norm_color(color);
	obj->m = matrix4_scale(radius, radius, radius);
	obj->m = matrix4_mul(matrix4_translate(pos.x, pos.y, pos.z), obj->m);
	obj->m_inv = matrix4_inv(obj->m);
	obj->m_inv_trans = matrix4_trans(obj->m_inv);
	return (obj);
}

t_object	*new_plan(t_point3 pos, t_vec3 normal, uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->fnct = &plane_intersection;
	obj->uvmap_fnct = &get_planar_map;
	obj->type = O_PLAN;
	obj->albedo = get_norm_color(color);
	obj->m = build_rotation_matrix(vec_norm(normal));
	obj->m = matrix4_mul(matrix4_translate(pos.x, pos.y, pos.z), obj->m);
	obj->m_inv = matrix4_inv(obj->m);
	obj->m_inv_trans = matrix4_trans(obj->m_inv);
	return (obj);
}

t_object	*new_cone(t_point3 pos, double diam_heig[2], t_vec3 orient,
		uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = O_CONE;
	obj->albedo = get_norm_color(color);
	obj->fnct = &intersect_cone;
	obj->uvmap_fnct = &get_cone_map;
	obj->m = matrix4_scale(diam_heig[0], diam_heig[1], diam_heig[0]);
	obj->m = matrix4_mul(build_rotation_matrix(vec_norm(orient)), obj->m);
	obj->m = matrix4_mul(matrix4_translate(pos.x, pos.y, pos.z), obj->m);
	obj->m_inv = matrix4_inv(obj->m);
	obj->m_inv_trans = matrix4_trans(obj->m_inv);
	return (obj);
}
