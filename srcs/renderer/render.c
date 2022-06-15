/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/15 14:42:49 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "plane.h"
#include "mlx.h"
#include "mlx_utils.h"
#include "define.h"
#include <stdio.h>
#include "vector.h"
#include <math.h>

static void	generate_ray(t_ray *ray, t_3dpoint viewport_point)
{
	ray->org = vec(0.0, 0.0, 0.0);
	ray->dir.x = viewport_point.x;
	ray->dir.y = viewport_point.y;
	ray->dir.z = viewport_point.z;
}

void	render_img(t_minirt *minirt)
{
	t_3dpoint	viewport_point;
	t_ray		ray;
	size_t		i;
	size_t		j;
	t_rayhit	rayhit;

	i = 0;
	j = 0;
	viewport_point.z = -WIDTH / (2 * tan(FOV / 2));
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			viewport_point.x = j - WIDTH / 2.0;
			viewport_point.y = i - HEIGHT / 2.0;
			generate_ray(&ray, viewport_point);
			rayhit = plane_intersection(vec(0.0, -10.0, 0.0), vec(0.0, 1.0, 0.0), ray);
			if (rayhit.t != -1)
				mlx_pixel_img_put(minirt, j, i, set_color(0, 255, 0));
			else
				mlx_pixel_img_put(minirt, j, i, set_color(0, 0, 255));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win, minirt->mlx.img.img, 0, 0);
}
