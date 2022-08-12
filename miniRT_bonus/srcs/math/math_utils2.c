/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:26:59 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 16:31:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "matrix.h"
#include "tuple.h"
#include "define.h"
#include "math_utils.h"
#include <stdbool.h>
#include <math.h>

/* Transform a given ray with a given matrix. */

t_ray	ray_transform(t_ray old_ray, t_matrix4 const M)
{
	t_ray	new_ray;

	new_ray.org = matrix4_tmul(M, old_ray.org);
	new_ray.dir = matrix4_tmul(M, old_ray.dir);
	return (new_ray);
}

t_point3	get_ray_point(t_ray ray, double t)
{
	return (tadd(ray.org, tmul_scalar(ray.dir, t)));
}

t_vec3	get_reflection_vec(t_vec3 incident, t_vec3 normal)
{
	t_vec3	reflectionv;

	reflectionv = tsub(tmul_scalar(normal, 2 * vec_dot(incident, normal)),
			incident);
	return (reflectionv);
}
