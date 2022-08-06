/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:43:00 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/06 16:59:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "ray_intersection.h"
#include "mlx_utils.h"
#include "texture.h"
#include "define.h"
#include "matrix.h"
#include "tuple.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

t_matrix4	build_rotation_matrix(t_vec3 orient)
{
	t_matrix4	M;
	double	alpha;
	double	beta;

	alpha = atan2(sqrt(orient.x * orient.x + orient.z * orient.z), orient.y);
	beta = atan2(orient.z, orient.x);
	M = matrix4_rotate_z(-alpha);
	M = matrix4_mul(matrix4_rotate_y(-beta), M); 
	return (M);
}

t_object	*new_cylinder(t_point3 pos, double diameter, double height, t_vec3 orient,
		uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.cylinder.diameter = diameter;
	obj->p.cylinder.half_height = height / 2;
	obj->type = T_CYLINDER;
	obj->albedo = get_norm_color(color);
	obj->fnct = &intersect_cylinder;
	obj->uvmap_fnct = &get_cylinder_map;
	obj->p.cylinder.pos = pos;
	obj->M = build_rotation_matrix(vec_norm(orient));
	obj->M = matrix4_mul(matrix4_scale(diameter, diameter, diameter), obj->M);
	obj->M = matrix4_mul(matrix4_translate(pos.x, pos.y, pos.z), obj->M);
	obj->M_inv = matrix4_inv(obj->M);
	obj->M_inv_trans = matrix4_trans(obj->M_inv);
	return (obj);
}

t_object	*new_sphere(t_point3 pos, double radius, uint32_t color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.sphere.pos = pos;
	obj->p.sphere.radius = radius;
	obj->fnct = &intersect_sphere;
	obj->uvmap_fnct = &get_spherical_map;
	obj->type = T_SPHERE;
	obj->albedo = get_norm_color(color);
	obj->M = matrix4_scale(radius, radius, radius);
	obj->M = matrix4_mul(matrix4_translate(pos.x, pos.y, pos.z), obj->M);
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
	obj->uvmap_fnct = &get_planar_map;
	obj->type = T_PLAN;
	obj->albedo = get_norm_color(color);
	obj->M = build_rotation_matrix(vec_norm(normal));
	obj->M = matrix4_mul(matrix4_translate(pos.x, pos.y, pos.z), obj->M);
	obj->M_inv = matrix4_inv(obj->M);
	obj->M_inv_trans = matrix4_trans(obj->M_inv);
	return (obj);
}

void	apply_obj_transform(t_object *obj, t_matrix4 const M)
{
	obj->M = M;
	obj->M_inv = matrix4_inv(M);
}
