/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:43:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 16:31:38 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "matrix_bonus.h"
#include "tuple_bonus.h"
#include "define_bonus.h"
#include "math_utils_bonus.h"
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

bool	fequals(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	else
		return (false);
}

double	sqr(double a)
{
	return (a * a);
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
