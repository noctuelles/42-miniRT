/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/15 19:46:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "define.h"
#include "mlx.h"
#include "mlx_utils.h"
#include "vector.h"
#include "scene.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

static void	generate_ray(t_ray *ray, t_3dpoint viewport_point)
{
	ray->org = vec(0.0, 0.0, 0.0);
	ray->dir.x = viewport_point.x;
	ray->dir.y = viewport_point.y;
	ray->dir.z = viewport_point.z;
	vec_normalize_p(&ray->dir);
}

void	render_img(t_minirt *minirt)
{
	t_3dpoint	viewport_point;
	t_ray		ray;
	size_t		i;
	size_t		j;


	/* Ici on definie tout nos objects pour debug. */

	add_obj_to_scene(&minirt->scene, new_sphere(
				vec(0, 0, -255),
				20.0,
				0xFFFF0000));
	add_obj_to_scene(&minirt->scene, new_sphere(
				vec(30, 80, -355),
				20.0,
				0xFF00FF00));
	add_obj_to_scene(&minirt->scene, new_sphere(
				vec(-30, 40, -155),
				20.0,
				0xFF0000FF));


	viewport_point.z = -WIDTH / (2 * tan(FOV / 2));
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			t_object	*closest_obj = NULL;

			viewport_point.x = j - WIDTH / 2.0;
			viewport_point.y = i - HEIGHT / 2.0;
			generate_ray(&ray, viewport_point);
			for (t_list *elem = minirt->scene.objs; elem; elem = elem->next)
			{
				t_object	*obj = elem->content;

				if (obj->fnct(obj, &ray)) // il y a intersection avec l'objet en question
				{
					if (!closest_obj)
					{
						closest_obj = obj;
					}
					else if (obj->rayhit.t < closest_obj->rayhit.t)
						closest_obj = obj;
				}
			}
			// Maintenant on gere la lumiere
			if (closest_obj)
				mlx_pixel_img_put(minirt, j, i, closest_obj->color);
			j++;
		}
		i++;
	}
	puts("Rendering done");
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win, minirt->mlx.img.img, 0, 0);
}
