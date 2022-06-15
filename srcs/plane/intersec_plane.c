/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:17:47 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/15 14:43:28 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "vector.h"

t_rayhit	plane_intersection(t_3dpoint point, t_vec3d normal, t_ray ray)
{
	t_rayhit	rayhit;

	rayhit.normal = normal;
	rayhit.t = vec_dot(normal, vec_sub(point, ray.org))
		/ vec_dot(normal, ray.dir);
	if (rayhit.t < 0 || vec_dot(normal, ray.dir) == 0)
		rayhit.t = -1;
	return (rayhit);
}
