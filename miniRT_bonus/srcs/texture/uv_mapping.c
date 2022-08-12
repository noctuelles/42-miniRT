/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:07:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 23:16:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "tuple.h" 
#include <math.h>
#include "define.h"

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
	phi = acos(intersect_p.y);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = 1 - (phi / M_PI);
	return (uv);
}

t_uv	get_cylinder_map(t_point3 intersect_p)
{
	t_uv	uv;
	double	theta;

	theta = atan2(intersect_p.x, intersect_p.z);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = fmod(intersect_p.y, 1);
	return (uv);
}

t_uv	get_cone_map(t_point3 intersect_p)
{
	t_uv	uv;
	double	theta;
	double	radius;

	radius = intersect_p.x * intersect_p.x + intersect_p.z * intersect_p.z;
	theta = atan2(intersect_p.x, intersect_p.z);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = fmod(sqrt(radius), 1);
	return (uv);
}
