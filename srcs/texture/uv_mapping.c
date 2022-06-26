/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:07:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/26 10:48:32 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "tuple.h" 
#include <math.h>

t_uv	get_planar_map(t_point3 intersect_p)
{
	t_uv	uv;

	uv.u = fmod(intersect_p.x, 1);
	uv.v = fmod(intersect_p.z, 1);
	return (uv);
}

t_uv	get_spherical_map(t_point3 intersect_p)
{
	t_uv	uv;
	double	theta;
	double	phi;

	theta = atan2(intersect_p.x, intersect_p.z);
	phi = acos(intersect_p.y / vec_mag(intersect_p));
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = 1 - (phi / M_PI);
	return (uv);
}
