/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:43:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/24 18:26:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "matrix.h"
#include "tuple.h"
#include "math_utils.h"
#include <stdbool.h>
#include <math.h>

double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

/* Solve a given quadratic equation with the given parameter. */

bool	solve_quadratic(double a, double b, double c, double t[2])
{
	double	discriminant;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (false);
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	return (true);
}

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
