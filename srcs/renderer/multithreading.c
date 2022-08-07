/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:57:05 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/07 16:54:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minirt_struct.h"
#include "scene.h"
#include "mlx_utils.h"
#include "math_utils.h"
#include "tuple.h"
#include <stdio.h>
#include "matrix.h"
#include <math.h>

uint32_t	get_color(t_color color)
{
		unsigned char r, g, b;

	r = min(255., min(1, color.x) * 255.99);
	g = min(255., min(1, color.y) * 255.99);
	b = min(255., min(1, color.z) * 255.99);
	return (r << 16 | g << 8 | b);
}

t_matrix4	build_view_matrix(t_vec3 orient)
{
	t_matrix4	transform;
	double		alpha;
	double		beta;

	orient = vec_norm(orient);
	alpha = atan2(orient.x, orient.z);
	beta = atan2(orient.y, sqrt(orient.x * orient.x + orient.z * orient.z));
	transform = matrix4_rotate_x(-beta);
	transform = matrix4_mul(matrix4_rotate_y(alpha), transform);
	return (transform);
}

static inline void	generate_ray(t_ray *ray, t_rayhit *rayhit, t_point3 viewport_point, t_matrix4 m)
{
	ray->org = point(0, 0, 0);
	ray->dir = vec_norm(matrix4_tmul(m, viewport_point));
	ray->dir.w = 0;
	rayhit->eyev = tnegate(ray->dir);
}

void	*render(void *pwrkrs)
{
	t_worker	*wrkr;
	t_point3	viewport_point;
	t_ray		ray;
	t_rayhit	rayhit;
	t_matrix4	vmatrix;
	size_t	i;
	size_t	j;

	wrkr = pwrkrs;
	i = wrkr->assigned_start;
	vmatrix = build_view_matrix(vector(0.0, 0, 1));
	viewport_point.z = WIDTH / (2 * tan(FOV / 2));
	while (i <= wrkr->assigned_end)
	{
		j = 0;
		while (j < WIDTH)
		{
			t_object	*obj;

			viewport_point.x = j - (WIDTH / 2.0);
			viewport_point.y = i - (HEIGHT / 2.0);
			generate_ray(&ray, &rayhit, viewport_point, vmatrix);
			obj = ray_intersect_scene_objs(&wrkr->minirt->scene,
					&ray, &rayhit);
			if (obj)
			{
				mlx_pixel_img_put(wrkr->minirt, j, i, get_color(
							get_shade(&wrkr->minirt->scene, obj, &rayhit)));
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	setup_workers(t_minirt *minirt)
{
	size_t	i;
	unsigned int	rows_per_worker;

	i = 0;
	rows_per_worker = HEIGHT / THREAD_NBR;
	while (i < THREAD_NBR)
	{
		minirt->workers[i].id = i;
		minirt->workers[i].minirt = minirt;
		minirt->workers[i].assigned_start = i * rows_per_worker;
		minirt->workers[i].assigned_end = minirt->workers[i].assigned_start
			+ rows_per_worker - 1;

		i++;
	}
	minirt->workers[THREAD_NBR - 1].assigned_end += HEIGHT % THREAD_NBR;
}

void	*launch_workers(t_minirt *minirt)
{
	size_t	i;
	
	i = 0;
	while (i < THREAD_NBR)
	{
		if (pthread_create(&minirt->workers[i].pthread, NULL, &render,
					&minirt->workers[i]))
			return (NULL);
		i++;
	}
	i = 0;
	while (i < THREAD_NBR)
		pthread_join(minirt->workers[i++].pthread, NULL);
	return (minirt);
}
