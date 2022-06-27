/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:09:25 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/27 12:26:12 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt_struct.h"
#include "ray_intersection.h"
#include "tuple.h"
#include <math.h>
#include "define.h"
#include <stdio.h>

//? https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/

void	cone_base(t_cone_utils *all_inter, t_object *obj, t_ray *ray)
{
	t_object	obj_tmp;

	obj_tmp.p.disk.center = tadd(obj->p.cone.top, tmul_scalar(obj->p.cone.direction, obj->p.cone.hauteur));
	obj_tmp.p.disk.normal = obj->p.cone.direction;
	obj_tmp.p.disk.rayon = obj->p.cone.rayon_base;
	all_inter->close_disk = intersect_disk(&obj_tmp, ray);
	if (all_inter->close_disk)
		all_inter->rayhit_close_disk = obj_tmp.rayhit;
}

bool	give_intersect_cone(t_object *obj, t_ray *ray, double distance[2])
{
	double	a;
	double	b;
	double	c;
	t_tuple top_org;
	double	cos_square;
	
	top_org = tsub(ray->org, obj->p.cone.top);
	cos_square = pow(cos(DG_RAD(obj->p.cone.angle)), 2);
	a = pow(vec_dot(ray->dir, obj->p.cone.direction), 2) - cos_square;
	b = 2 * (vec_dot(ray->dir, obj->p.cone.direction) * vec_dot(top_org , obj->p.cone.direction) - vec_dot(ray->dir, tmul_scalar(top_org, cos_square)));
	c = pow(vec_dot(top_org, obj->p.cone.direction), 2) - vec_dot(top_org, tmul_scalar(top_org, cos_square));
	return(solve_quadratic(a, b, c, distance));
}

t_vec3 find_normal_cone(t_object *obj, t_rayhit rayhit, t_ray *ray)
{
	double distance;
	t_point3 point;

	distance = vec_mag(tsub(obj->p.cone.top, rayhit.intersect_p));
	point = tadd(obj->p.cone.top, tmul_scalar(obj->p.cone.direction, distance));
	return (vec_norm(tsub(rayhit.intersect_p, point)));
}

void	intersect_cone_inf(t_cone_utils *all_inter, t_object *obj, t_ray *ray)
{
	double		distance[2];
	
	if (give_intersect_cone(obj, ray, distance))
	{
		//* First
		all_inter->rayhit_first_inter.intersect_p = get_ray_point(*ray, distance[0]);
		if (vec_dot(tsub(all_inter->rayhit_first_inter.intersect_p, obj->p.cone.top), obj->p.cone.direction) > 0)
		{
			all_inter->first_inter = true;
			all_inter->rayhit_first_inter.t = distance[0];
			all_inter->rayhit_first_inter.normal = find_normal_cone(obj, all_inter->rayhit_first_inter, ray);
		}
		//* Second
		all_inter->rayhit_second_inter.intersect_p = get_ray_point(*ray, distance[1]);
		if (vec_dot(tsub(all_inter->rayhit_second_inter.intersect_p, obj->p.cone.top), obj->p.cone.direction) > 0)
		{
			all_inter->second_inter = true;
			all_inter->rayhit_second_inter.t = distance[1];
			all_inter->rayhit_second_inter.normal = find_normal_cone(obj, all_inter->rayhit_second_inter, ray);
		}
	}
}

bool	select_first_intersect_cone(t_cone_utils *all_inter, t_object *obj, t_rayhit *rayhit)
{
	bool		retour;

	retour = false;
	if (all_inter->first_inter)
	{
		retour = true;
		*rayhit = all_inter->rayhit_first_inter;
	}
	if (all_inter->second_inter && (retour == false || rayhit->t > all_inter->rayhit_second_inter.t))
	{
		retour = true;
		*rayhit = all_inter->rayhit_second_inter;
	}
	if (all_inter->close_disk && (retour == false || rayhit->t > all_inter->rayhit_close_disk.t))
	{
		retour = true;
		*rayhit = all_inter->rayhit_close_disk;
	}
	return (retour);
}

void	cut_cone_inf(t_cone_utils *all_inter, t_object *obj)
{
	double len;

	if (all_inter->first_inter)
	{
		len = vec_mag(tsub(obj->p.cone.top, all_inter->rayhit_first_inter.intersect_p));
		if (len > obj->p.cone.len_pente)
			all_inter->first_inter = false;
	}
	if (all_inter->second_inter)
	{
		len = vec_mag(tsub(obj->p.cone.top, all_inter->rayhit_second_inter.intersect_p));
		if (len > obj->p.cone.len_pente)
			all_inter->second_inter = false;
	}
}

bool	intersect_cone(t_object *obj, t_ray *ray, t_rayhit *rayhit)
{
	t_ray			new_ray;
	t_cone_utils	all_inter;

	all_inter.close_disk = false;
	all_inter.first_inter = false;
	all_inter.second_inter = false;
	cone_base(&all_inter, obj, ray);
	intersect_cone_inf(&all_inter, obj, ray);
	cut_cone_inf(&all_inter, obj);
	return (select_first_intersect_cone(&all_inter, obj, rayhit));
}