/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:43:00 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/04 20:16:28 by plouvel          ###   ########.fr       */
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

t_matrix4	build_rotation_f(t_vec3 up)
{
	t_matrix4	M;
	t_vec3	right;
	t_vec3	forward = vector(0, 0, 1);
	t_vec3	true_forward;

	right = vec_norm(vec_cross(up, forward));
	true_forward = vec_norm(vec_cross(right, up));
	forward = true_forward;

	memset(&M, 0, sizeof(t_matrix4));
	M.m[0][0] = right.x;
	M.m[1][0] = up.x;
	M.m[2][0] = forward.x;

	M.m[0][1] = right.y;
	M.m[1][1] = up.y;
	M.m[2][1] = forward.y;

	M.m[0][2] = right.z;
	M.m[1][2] = up.z;
	M.m[2][2] = forward.z;

	print_matrix4(M);
	M.m[3][3] = 1.;
	return (M);

}

t_matrix4 build_rotation(t_vec3 direction)
{
	t_matrix4	M;
	t_vec3		xaxis;
	t_vec3		yaxis;
	t_vec3		zaxis;

	xaxis = vec_norm(vec_cross(vector(0, 1, 0), direction));
	yaxis = vec_norm(vec_cross(direction, xaxis));
	zaxis = direction;

	/*xaxis = vec_norm(vector(1, 0, 0));
	yaxis = vec_norm(vector(0, 1, 0));
	zaxis = vec_norm(vector(0, 0, 1));*/

	memset(&M, 0, sizeof(t_matrix4));
	M.m[0][0] = xaxis.x;
	M.m[1][0] = yaxis.x;
	M.m[2][0] = zaxis.x;

	M.m[0][1] = xaxis.y;
	M.m[1][1] = yaxis.y;
	M.m[2][1] = zaxis.y;

	M.m[0][2] = xaxis.z;
	M.m[1][2] = yaxis.z;
	M.m[2][2] = zaxis.z;

	M.m[3][3] = 1.;
	puts("");
	print_matrix4(M);
	puts("");
	return (M);
}

t_object	*new_cylinder(t_point3 pos, double diameter, double height, t_vec3 orientation,
		uint32_t color)
{
	t_object	*obj;
	double		alpha = 0.;
	double		beta = 0.;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.cylinder.diameter = diameter;
	obj->p.cylinder.half_height = height / 2;
	obj->type = T_CYLINDER;
	obj->albedo = get_norm_color(color);
	obj->fnct = &intersect_cylinder;
	obj->p.cylinder.pos = pos;
	orientation = vec_norm(orientation);
	alpha = atan2(sqrt(orientation.x * orientation.x + orientation.z * orientation.z), orientation.y);
	beta = atan2(orientation.z, orientation.x);
	printf("alpha: %f\n", alpha * 180 / M_PI);
	printf("beta: %f\n", beta * 180 / M_PI);
	obj->M = matrix4_rotate_z(-alpha);
	obj->M = matrix4_mul(matrix4_rotate_y(-beta), obj->M);
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
	double		alpha;
	double		beta;


	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->p.plan.pos = pos;
	obj->p.plan.normal = normal;
	obj->fnct = &plane_intersection;
	obj->uvmap_fnct = &get_planar_map;
	obj->type = T_PLAN;
	obj->albedo = get_norm_color(color);
	tprint(normal);
	normal = vec_norm(normal);
	tprint(normal);
	alpha = atan2(sqrt(normal.x * normal.x + normal.z * normal.z), normal.y);
	beta = atan2(normal.z, normal.x);
	obj->M = matrix4_rotate_z(-alpha);
	obj->M = matrix4_mul(matrix4_rotate_y(-beta), obj->M);
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
