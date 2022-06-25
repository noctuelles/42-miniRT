/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instersect_cylindre.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:24:21 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/25 16:18:04 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt_struct.h"
#include "ray_intersection.h"
#include "tuple.h"
#include "matrix.h"
#include <math.h>
#include <stdio.h>

//http://heigeas.free.fr/laure/ray_tracing/cylindre.html

void	up_disk_cylindre(t_cyl_utils *all_inter, t_object *obj, t_ray *ray)
{
	t_object	obj_tmp;

	obj_tmp.p.disk.center = tadd(obj->p.cylindre.center, tmul_scalar(obj->p.cylindre.orientation, obj->p.cylindre.hauteur / 2.0));
	obj_tmp.p.disk.normal = obj->p.cylindre.orientation;
	obj_tmp.p.disk.rayon = obj->p.cylindre.rayon;
	all_inter->up_disk = intersect_disk(&obj_tmp, ray);
	if (all_inter->up_disk)
		all_inter->rayhit_up_disk = obj_tmp.rayhit;
}

void	down_disk_cylindre(t_cyl_utils *all_inter, t_object *obj, t_ray *ray)
{
	t_object	obj_tmp;

	obj_tmp.p.disk.center = tsub(obj->p.cylindre.center, tmul_scalar(obj->p.cylindre.orientation, (obj->p.cylindre.hauteur / 2.0)));
	obj_tmp.p.disk.normal = obj->p.cylindre.orientation;
	obj_tmp.p.disk.rayon = obj->p.cylindre.rayon;
	all_inter->down_disk = intersect_disk(&obj_tmp, ray);
	if (all_inter->down_disk)
		all_inter->rayhit_down_disk = obj_tmp.rayhit;
}

bool	give_intersec_normalize_cylinder(double rayon, t_ray *new_ray, double distance[2])
{
	double	delta;
	double	a;
	double	b;
	double	c;

	a = (new_ray->dir.y * new_ray->dir.y) + (new_ray->dir.z * new_ray->dir.z);
	b = 2 * ((new_ray->dir.y * new_ray->org.y) + (new_ray->dir.z * new_ray->org.z));
	c = (new_ray->org.y * new_ray->org.y) + (new_ray->org.z * new_ray->org.z) - (rayon * rayon);
	return (solve_quadratic(a, b, c, distance));
}

void	intersect_paille_inf(t_cyl_utils *all_inter, t_object *obj, t_ray *ray)
{
	double		distance[2];
	
	if (give_intersec_normalize_cylinder(obj->p.cylindre.rayon, ray, distance))
	{
		//* First
		all_inter->first_paille = true;
		all_inter->rayhit_first_paille.t = distance[0];
		all_inter->rayhit_first_paille.intersect_p = get_ray_point(*ray, distance[0]);
		all_inter->rayhit_first_paille.normal = vector(0, all_inter->rayhit_first_paille.intersect_p.y, all_inter->rayhit_first_paille.intersect_p.z);
		all_inter->rayhit_first_paille.intersect_p = matrix4_tmul(obj->M, all_inter->rayhit_first_paille.intersect_p);
		all_inter->rayhit_first_paille.normal = matrix4_tmul(obj->M, all_inter->rayhit_first_paille.normal);
		//* Second
		all_inter->second_paille = true;
		all_inter->rayhit_second_paille.t = distance[1];
		all_inter->rayhit_second_paille.intersect_p = get_ray_point(*ray, distance[0]);
		all_inter->rayhit_second_paille.normal = vector(0, all_inter->rayhit_second_paille.intersect_p.y, all_inter->rayhit_first_paille.intersect_p.z);
		all_inter->rayhit_second_paille.intersect_p = matrix4_tmul(obj->M, all_inter->rayhit_second_paille.intersect_p);
		all_inter->rayhit_second_paille.normal = matrix4_tmul(obj->M, all_inter->rayhit_second_paille.normal);
	}
}

bool	select_first_intersect(t_cyl_utils *all_inter, t_object *obj, t_rayhit *rayhit)
{
	bool		retour;

	retour = false;
	if (all_inter->first_paille)
	{
		retour = true;
		*rayhit = all_inter->rayhit_first_paille;
	}
	if (all_inter->second_paille && (retour == false || rayhit->t > all_inter->rayhit_second_paille.t))
	{
		retour = true;
		*rayhit = all_inter->rayhit_second_paille;
	}
	if (all_inter->up_disk && (retour == false || rayhit->t > all_inter->rayhit_up_disk.t))
	{
		retour = true;
		*rayhit = all_inter->rayhit_up_disk;
	}
	if (all_inter->down_disk && (retour == false || rayhit->t > all_inter->rayhit_down_disk.t))
	{
		retour = true;
		*rayhit = all_inter->rayhit_down_disk;
	}
	return (retour);
}

bool	intersect_cylindre(t_object *obj, t_ray *ray, t_rayhit *rayhit)
{
	t_ray		new_ray;
	t_cyl_utils	all_inter;

	all_inter.up_disk = false;
	all_inter.down_disk = false;
	all_inter.first_paille = false;
	all_inter.second_paille = false;
	new_ray = ray_transform(*ray, obj->M_inv);
	up_disk_cylindre(&all_inter, obj, ray);
	down_disk_cylindre(&all_inter, obj, ray);
	intersect_paille_inf(&all_inter, obj, &new_ray);
	return (select_first_intersect(&all_inter, obj, rayhit));
}
