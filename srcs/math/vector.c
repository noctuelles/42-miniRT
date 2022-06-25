/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:45:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 22:00:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "tuple.h"
#include <math.h>

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y +  a.z * b.z);
}

double	vec_mag(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec_norm(t_vec3 a)
{
	double	inv_mag;

	inv_mag = 1. / vec_mag(a);
	return (vector(a.x * inv_mag, a.y * inv_mag, a.z * inv_mag));
}

double	vec_mag_sqr(t_vec3 a)
{
	return (vec_dot(a, a));
}
