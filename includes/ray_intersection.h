/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:23:08 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/27 16:01:19 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INTERSECTION_H
# define RAY_INTERSECTION_H

# include "minirt_struct.h"

/*
 *	intersect_sphere.c
 */

bool	intersect_sphere(t_object *obj, t_ray *ray, t_rayhit *rayhit);

/*
 *	intersect_plane.c
 */

bool	plane_intersection(t_object *object, t_ray *ray, t_rayhit *rayhit);

/*
 *	intersect_cylindre.c
 */

bool	intersect_cylindre(t_object *obj, t_ray *ray, t_rayhit *rayhit);
bool	intersect_disk(t_object *obj, t_ray *ray);

/*
 *	intersect_cone.c
 */

bool	intersect_cone(t_object *obj, t_ray *ray, t_rayhit *rayhit);

/*
 *	intersect_cone_utils.c
 */

t_vec3	find_normal_cone(t_object *obj, t_rayhit rayhit, t_ray *ray);
bool	give_intersect_cone(t_object *obj, t_ray *ray, double distance[2]);

#endif
