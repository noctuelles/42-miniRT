/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/16 17:38:03 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "define.h"
#include "mlx.h"
#include "mlx_utils.h"
#include "vector.h"
#include "scene.h"
#include <math.h>
#include "math_utils.h"
#include <limits.h>
#include <stdio.h>

static void	generate_ray(t_ray *ray, t_3dpoint viewport_point)
{
	ray->org = vec(0.0, 0.0, 0.0);
	ray->dir = vec_normalize(viewport_point);
}

t_color	compute_light(t_object *obj, t_light *light)
{
	t_color	color = {0};
	double	dot_normal_light;
	t_vec3d	normal_to_light;

	normal_to_light = vec_sub(light->point, obj->rayhit.intersect_p);
	dot_normal_light = max(0.2, vec_dot(vec_normalize(normal_to_light),
			obj->rayhit.normal));
	color = vec_mul_scalar(obj->albedo,
			1e6 * light->ratio * dot_normal_light / vec_lenght_p(normal_to_light));
	return (color);
}

uint32_t	get_color(t_color color)
{
	unsigned char r, g, b;

	r = min(255., color.x);
	g = min(255., color.y);
	b = min(255., color.z);
	return (r << 16 | g << 8 | b);
}

void	render_img(t_minirt *minirt)
{
	t_3dpoint	viewport_point;
	t_ray		ray;
	size_t		i;
	size_t		j;


	/* Ici on definie tout nos objects pour debug. */

	add_obj_to_scene(&minirt->scene, new_sphere(
				vec(0, 0, -55),
				8.0,
				0xff0000));

	// le sol

	add_obj_to_scene(&minirt->scene, new_plan(
				vec(0, -1, 0),
				vec(0, 1, -0.3),
				0xbfbfe0));

	/* Pour l'instant, l'unique lumiere */

	set_scene_light(&minirt->scene,
				vec(0, 57, -70),
				1);


	viewport_point.z = - (WIDTH / (2 * tan(FOV / 2)));
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			t_object	*closest_obj = NULL;

			viewport_point.x = j - (WIDTH / 2.0);
			viewport_point.y = i - (HEIGHT / 2.0);
			generate_ray(&ray, viewport_point);
			for (t_list *elem = minirt->scene.objs; elem; elem = elem->next)
			{
				t_object	*obj = elem->content;

				if (obj->fnct(obj, &ray)) // il y a intersection avec l'objet en question
				{
					if (!closest_obj)
						closest_obj = obj;
					else if (obj->rayhit.t < closest_obj->rayhit.t)
						closest_obj = obj;
				}
			}
			if (closest_obj)
			{
				mlx_pixel_img_put(minirt, j, i, get_color(compute_light(closest_obj, &minirt->scene.light)));
			}
			else
			{
				unsigned char r, g, b;

				r = 16 + (double) (255 - 16) / HEIGHT * i;
				g = 112 + (double) (255 - 112) / HEIGHT * i;
				b = 222 + (double) (255 - 222) / HEIGHT * i;
				mlx_pixel_img_put(minirt, j, i, 0xFF << 24| r << 16 | g << 8 | b);
			}
			j++;
		}
		i++;
	}
	puts("Rendering done");
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win, minirt->mlx.img.img, 0, 0);
}
