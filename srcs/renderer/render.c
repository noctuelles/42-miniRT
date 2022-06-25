/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 20:38:18 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "matrix.h"
#include "define.h"
#include "mlx.h"
#include "mlx_utils.h"
#include "tuple.h"
#include "scene.h"
#include <math.h>
#include "math_utils.h"
#include <limits.h>
#include <stdio.h>
#include <stdint.h>

static inline void	generate_ray(t_ray *ray, t_point3 viewport_point)
{
	ray->org = point(0.0, 2., 0);
	ray->dir = vec_norm(viewport_point);
	ray->dir.w = 0;
}

/*
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
*/

uint32_t	get_color(t_color color)
{
		unsigned char r, g, b;

	r = min(255., color.x * 255.);
	g = min(255., color.y * 255.);
	b = min(255., color.z * 255.);
	return (r << 16 | g << 8 | b);
}

/*double	get_lambertian_factor(t_object *obj, t_light *light,
		t_vec3 lightv, t_vec3 normal)
{
	double	dot;

	dot = max(0, vec_dot(normal, lightv));
	return (dot);
}*/

void	render_img(t_minirt *minirt)
{
	t_point3	viewport_point;
	t_ray		ray;
	t_rayhit	rayhit;
	size_t		i;
	size_t		j;

	add_obj_to_scene(&minirt->scene, new_sphere(point(0, 1, 20), 2, 0xFF0000));
	add_obj_to_scene(&minirt->scene, new_plan(point(0, -1, 0), vector(0, 1, 0), 0xeeeeee));
	add_light_to_scene(&minirt->scene, point(0, 30, 10), 0xFFFFFF, 0.4);
	set_ambiant_light(&minirt->scene, 0xFFFFFF, 0.2);

	viewport_point.z = WIDTH / (2 * tan(FOV / 2));
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			t_object	*obj;

			viewport_point.x = j - (WIDTH / 2.0);
			viewport_point.y = i - (HEIGHT / 2.0);
			generate_ray(&ray, viewport_point);
			obj = ray_intersect_scene_objs(&minirt->scene, &ray, &rayhit);
			if (obj)
			{
				mlx_pixel_img_put(minirt, j, i, get_color(
							get_shade(&minirt->scene, obj, &rayhit)));
			}
			j++;
		}
		i++;
	}
	puts("Rendering done");
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win, minirt->mlx.img.img, 0, 0);
}
