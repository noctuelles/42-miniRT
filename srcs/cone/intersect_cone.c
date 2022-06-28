/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:09:25 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/28 11:13:27 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt_struct.h"
#include "ray_intersection.h"
#include "tuple.h"
#include <math.h>
#include "define.h"

void	cone_base(t_cone_utils *utils, t_object *obj, t_ray *ray)
{
	t_object	obj_tmp;

	obj_tmp.p.disk.center = tadd(obj->p.cone.top,
			tmul_scalar(obj->p.cone.dir, obj->p.cone.height));
	obj_tmp.p.disk.normal = obj->p.cone.dir;
	obj_tmp.p.disk.rayon = obj->p.cone.rayon_base;
	utils->close_disk = intersect_disk(&obj_tmp, ray);
	if (utils->close_disk)
		utils->rayhit_close_disk = obj_tmp.rayhit;
}

void	intersect_cone_inf(t_cone_utils *utils, t_object *obj, t_ray *ray)
{
	double		distance[2];

	if (give_intersect_cone(obj, ray, distance))
	{
		utils->rayhit_first.intersect_p = get_ray_point(*ray, distance[0]);
		if (vec_dot(tsub(utils->rayhit_first.intersect_p,
					obj->p.cone.top), obj->p.cone.dir) > 0)
		{
			utils->first = true;
			utils->rayhit_first.t = distance[0];
			utils->rayhit_first.normal = find_normal_cone(obj,
					utils->rayhit_first, ray);
		}
		utils->rayhit_second.intersect_p = get_ray_point(*ray, distance[1]);
		if (vec_dot(tsub(utils->rayhit_second.intersect_p,
					obj->p.cone.top), obj->p.cone.dir) > 0)
		{
			utils->second = true;
			utils->rayhit_second.t = distance[1];
			utils->rayhit_second.normal = find_normal_cone(obj,
					utils->rayhit_second, ray);
		}
	}
}

bool	first_inter_cone(t_cone_utils *utils, t_object *obj, t_rayhit *rayhit)
{
	bool		retour;

	retour = false;
	if (utils->first)
	{
		retour = true;
		*rayhit = utils->rayhit_first;
	}
	if (utils->second && (retour == false
			|| rayhit->t > utils->rayhit_second.t))
	{
		retour = true;
		*rayhit = utils->rayhit_second;
	}
	if (utils->close_disk && (retour == false
			|| rayhit->t > utils->rayhit_close_disk.t))
	{
		retour = true;
		*rayhit = utils->rayhit_close_disk;
	}
	return (retour);
}

void	cut_cone_inf(t_cone_utils *utils, t_object *obj)
{
	double	len;

	if (utils->first)
	{
		len = vec_mag(tsub(obj->p.cone.top, utils->rayhit_first.intersect_p));
		if (len > obj->p.cone.len_pente)
			utils->first = false;
	}
	if (utils->second)
	{
		len = vec_mag(tsub(obj->p.cone.top, utils->rayhit_second.intersect_p));
		if (len > obj->p.cone.len_pente)
			utils->second = false;
	}
}

bool	intersect_cone(t_object *obj, t_ray *ray, t_rayhit *rayhit)
{
	t_ray			new_ray;
	t_cone_utils	utils;

	utils.close_disk = false;
	utils.first = false;
	utils.second = false;
	cone_base(&utils, obj, ray);
	intersect_cone_inf(&utils, obj, ray);
	cut_cone_inf(&utils, obj);
	return (first_inter_cone(&utils, obj, rayhit));
}
