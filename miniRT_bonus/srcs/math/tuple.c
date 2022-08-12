/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:00:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/04 20:16:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"

t_tuple	tuple(double x, double y, double z, double w)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (tuple);
}

t_vec3	vector(double x, double y, double z)
{
	return (tuple(x, y, z, 0));
}

t_point3	point(double x, double y, double z)
{
	return (tuple(x, y, z, 1));
}

t_tuple	tadd(t_tuple a, t_tuple b)
{
	return (tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}

t_tuple	tsub(t_tuple a, t_tuple b)
{
	return (tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}
