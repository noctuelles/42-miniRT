/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 18:32:07 by bsavinel         ###   ########.fr       */
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
	color = tmul_scalar(obj->albedo,
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

t_color	get_light(t_object *obj, t_rayhit *rayhit, t_light light)
{
	t_vec3	lightv;
	double	dot;

	lightv = vec_norm(tsub(light.pos, rayhit->intersect_p));
	dot = vec_dot(rayhit->normal, lightv);
	if (dot < 0)
		dot = 0;
	return (tmul_scalar(obj->albedo, dot));
}

void	render_img(t_minirt *minirt)
{
	t_point3	viewport_point;
	t_ray		ray;
	t_rayhit	rayhit;
	size_t		i;
	size_t		j;

	//add_obj_to_scene(&minirt->scene, new_sphere(point(0, 2, 20), 2, 0xFF0000));
	//add_obj_to_scene(&minirt->scene, new_sphere(point(-3, 1, 10), 2, 0x00FF00));
	add_obj_to_scene(&minirt->scene, new_plan(point(0, -1, 0), vector(0, 1, 0), 0xeeeeee));
	set_scene_light(&minirt->scene, point(0, 10, -5), 1.0); 
	//add_obj_to_scene(&minirt->scene, new_cylindre(point(0, 2, 40), vector(1, 1, 1), 2, 10, 0xFF0000));
	add_obj_to_scene(&minirt->scene, new_cone(point(0, 1, 5), vector(0, -1, 0), 20, 3, 0xFF0000));
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
				mlx_pixel_img_put(minirt, j, i, get_color(get_light(obj, &rayhit, minirt->scene.light)));
			}
			j++;
		}
		i++;
	}
	puts("Rendering done");
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win, minirt->mlx.img.img, 0, 0);
}
