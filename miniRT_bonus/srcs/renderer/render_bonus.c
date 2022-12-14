/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 16:05:05 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "end_bonus.h"
#include "mlx.h"
#include "mlx_utils_bonus.h"
#include "scene_bonus.h"
#include "math_utils_bonus.h"
#include "multithreading_bonus.h"
#include "ft_dprintf.h"
#include <unistd.h>
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

static inline uint64_t	get_mlsec_time(struct timeval t)
{
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	*render(void *pwrkrs)
{
	t_worker	*wrkr;
	t_ray		ray;
	t_rayhit	rayhit;
	t_object	*obj;
	t_point2	rp;

	wrkr = pwrkrs;
	rp.y = wrkr->assigned_start;
	while (rp.y <= wrkr->assigned_end)
	{
		rp.x = 0;
		while (rp.x < WIDTH)
		{
			generate_ray(&wrkr->minirt->camera, &ray, &rayhit, &rp);
			obj = ray_intersect_scene_objs(&wrkr->minirt->scene, &ray, &rayhit);
			if (obj)
				mlx_pixel_img_put(wrkr->minirt, rp.x, rp.y, get_color(
						get_shade(&wrkr->minirt->scene, obj, &rayhit)));
			rp.x++;
		}
		rp.y++;
	}
	return (NULL);
}

bool	render_img(t_minirt *minirt)
{
	struct timeval	t;
	struct timeval	t1;

	printf("minirt: rendering scene...\n");
	gettimeofday(&t, NULL);
	if (!launch_workers(minirt))
	{
		ft_dprintf(STDERR_FILENO, STR_BAD_THREAD);
		free_program(minirt);
		return (false);
	}
	gettimeofday(&t1, NULL);
	printf("minirt: rendered in %lu mlsec.\n",
		get_mlsec_time(t1) - get_mlsec_time(t));
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win,
		minirt->mlx.img.img, 0, 0);
	return (true);
}
