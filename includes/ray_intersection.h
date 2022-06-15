/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:23:08 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/15 18:26:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INTERSECTION_H
# define RAY_INTERSECTION_H

# include "minirt_struct.h"

bool	intersect_sphere(t_object *obj, t_ray *ray, t_rayhit *rayhit);

#endif
