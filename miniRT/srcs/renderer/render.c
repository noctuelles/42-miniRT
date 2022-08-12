/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 14:56:07 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "mlx.h"
#include "mlx_utils.h"
#include "scene.h"
#include "math_utils.h"
#include <stdio.h>
#include <sys/time.h>

static inline uint32_t	get_color(t_color color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = min(255., min(1, color.x) * 255.99);
	g = min(255., min(1, color.y) * 255.99);
	b = min(255., min(1, color.z) * 255.99);
	return (r << 16 | g << 8 | b);
}

void	render(t_minirt *minirt)
{
	t_ray		ray;
	t_rayhit	rayhit;
	t_object	*obj;
	t_point2	rp;

	rp.y = 0;
	while (rp.y < minirt->camera.screen_height)
	{
		rp.x = 0;
		while (rp.x < minirt->camera.screen_width)
		{
			generate_ray(&minirt->camera, &ray, &rayhit, &rp);
			obj = ray_intersect_scene_objs(&minirt->scene, &ray, &rayhit);
			if (obj)
				mlx_pixel_img_put(minirt, rp.x, rp.y, get_color(
						get_shade(&minirt->scene, obj, &rayhit)));
			rp.x++;
		}
		rp.y++;
	}
}

void	render_img(t_minirt *minirt)
{
	printf("minirt: rendering scene...\n");
	render(minirt);
	printf("minirt: render done.\n");
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win,
		minirt->mlx.img.img, 0, 0);
}
