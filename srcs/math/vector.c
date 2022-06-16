/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:45:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/16 16:40:00 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include <math.h>
#include <stdio.h>

void	vec_print(t_vec a)
{
	printf("(%.2f, %.2f, %.2f)\n", a.x, a.y, a.z);
}

t_vec	vec(double x, double y, double z)
{
	t_vec	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	return (vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return (vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	vec_mul_scalar(t_vec a, double scalar)
{
	return (vec(a.x * scalar, a.y * scalar, a.z * scalar));
}

double	vec_length(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

void	vec_normalize_p(t_vec *a)
{
	double	lenght;

	lenght = 1 / vec_length(*a);
	a->x *= lenght;
	a->y *= lenght;
	a->z *= lenght;
}

t_vec	vec_normalize(t_vec a)
{
	double	lenght;

	lenght = 1 / vec_length(a);
	return (vec(a.x * lenght, a.y * lenght, a.z * lenght));
}

double	vec_lenght_p(t_vec a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}
