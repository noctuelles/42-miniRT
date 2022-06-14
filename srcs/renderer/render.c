/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/14 16:12:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "define.h"
#include "vector.h"
#include <math.h>

static void	generate_ray(t_ray *ray, t_3dpoint viewport_point)
{
	ray->org = vec(0, 0, 0);
	ray->dir.x = viewport_point.x;
	ray->dir.y = viewport_point.y;
	ray->dir.z = viewport_point.z;
}

void	render_img(t_minirt *minirt)
{
	t_3dpoint	viewport_point;
	t_ray		ray;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	viewport_point.z = - WIDTH / (2 * tan(FOV / 2));
	(void) minirt;
	while (i < HEIGHT)
	{
		while (j < WIDTH)
		{
			viewport_point.x = j - WIDTH / 2.0;
			viewport_point.y = i - HEIGHT / 2.0;
			generate_ray(&ray, viewport_point);

			j++;
		}
		i++;
	}
}

