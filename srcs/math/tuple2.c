/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:02:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/24 17:06:28 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include <stdio.h>

t_tuple	tnegate(t_tuple a)
{
	t_tuple t;

	t.x = -a.x;
	t.y = -a.y;
	t.z = -a.z;
	t.w = -a.w;
	return (t);
}

void	tprint(t_tuple a)
{
	printf("{%5.2f, %5.2f, %5.2f, %5.2f}\n", a.x, a.y, a.z, a.w);
}
