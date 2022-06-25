/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:23:08 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 15:06:36 by bsavinel         ###   ########.fr       */
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

#endif
