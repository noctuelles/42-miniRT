/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:02:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 16:25:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "tuple_bonus.h"
#include <stdio.h>

t_tuple	tnegate(t_tuple a)
{
	t_tuple	t;

	t.x = -a.x;
	t.y = -a.y;
	t.z = -a.z;
	t.w = -a.w;
	return (t);
}

t_tuple	tmul(t_tuple a, t_tuple b)
{
	return (tuple(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w));
}

t_tuple	tmul_scalar(t_tuple a, double s)
{
	return (tuple(a.x * s, a.y * s, a.z * s, a.w * s));
}

void	tprint(t_tuple a)
{
	printf("{%5.2f, %5.2f, %5.2f, %5.2f}\n", a.x, a.y, a.z, a.w);
}
