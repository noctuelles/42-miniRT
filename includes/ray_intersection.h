/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:23:08 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 15:31:58 by plouvel          ###   ########.fr       */
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
bool	intersect_cylinder(t_object *obj, t_ray *ray, t_rayhit *rayhit);
bool	intersect_cone(t_object *obj, t_ray *ray, t_rayhit *rayhit);

#endif
