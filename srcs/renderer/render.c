/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/26 13:15:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "matrix.h"
#include "define.h"
#include "mlx.h"
#include "mlx_utils.h"
#include "tuple.h"
#include "texture.h"
#include "scene.h"
#include <math.h>
#include "math_utils.h"
#include <limits.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

static inline void	generate_ray(t_ray *ray, t_point3 viewport_point)
{
	ray->org = point(-5, 3, 0);
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

	r = min(255., min(1, color.x) * 255.99);
	g = min(255., min(1, color.y) * 255.99);
	b = min(255., min(1, color.z) * 255.99);
	return (r << 16 | g << 8 | b);
}

/*double	get_lambertian_factor(t_object *obj, t_light *light,
		t_vec3 lightv, t_vec3 normal)
{
	double	dot;

	dot = max(0, vec_dot(normal, lightv));
	return (dot);
}*/

uint64_t	get_mlsec_time(struct timeval t)
{
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	render_img(t_minirt *minirt)
{
	t_point3	viewport_point;
	t_ray		ray;
	t_rayhit	rayhit;
	size_t		i;
	t_object	*cobj;
	size_t		j;

	//add_obj_to_scene(&minirt->scene, new_sphere(point(4, 0, 8), 1, 0xFFFFFF));
	puts("loading texture");
	t_texture earth = create_image_texture(minirt->mlx.ptr, "textures/earth.xpm");
	t_texture moon = create_image_texture(minirt->mlx.ptr, "textures/moon.xpm");
	t_texture tennis = create_image_texture(minirt->mlx.ptr, "textures/tennis.xpm");
	puts("done");

	cobj = add_obj_to_scene(&minirt->scene, new_sphere(point(-5, 3, 15), 3, 0x00FF00));
	apply_obj_texture(cobj, earth);

	cobj = add_obj_to_scene(&minirt->scene, new_sphere(point(4, 3, 10), 2, 0x00FF00));
	apply_obj_texture(cobj, moon);

	cobj = add_obj_to_scene(&minirt->scene, new_sphere(point(3, 7, 18), 1, 0x00FF00));
	apply_obj_texture(cobj, tennis);

	cobj = add_obj_to_scene(&minirt->scene, new_plan(point(0, -1, 0), vector(0, 1, 0), 0xeeeeee));
	apply_obj_texture(cobj, create_checkered_texture(4, 4, 0xFFFFFF, 0x000000));

	add_light_to_scene(&minirt->scene, point(0, 5, 0), 0xFFFFFF, 1);
	//add_light_to_scene(&minirt->scene, point(0, 10, 35), 0xFFFFFF, 0.5);
	set_ambiant_light(&minirt->scene, 0xFF00FF, 0.0);


	viewport_point.z = WIDTH / (2 * tan(FOV / 2));
	i = 0;
	struct timeval	t, t1;
	gettimeofday(&t, NULL);
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
		double	percentage = (double) i / HEIGHT * 100;
		char	str[20];

		sprintf(str, "Rendering... %.2f\n", percentage);
		mlx_clear_window(minirt->mlx.ptr, minirt->mlx.win);
		mlx_string_put(minirt->mlx.ptr, minirt->mlx.win, WIDTH / 2 - strlen(str) * 4, HEIGHT / 2, 0xFFFFFF, str);
		i++;
	}
	gettimeofday(&t1, NULL);
	printf("Rendered in %lu mlsec.\n", get_mlsec_time(t1) - get_mlsec_time(t));
	puts("Rendering done");
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win, minirt->mlx.img.img, 0, 0);
}
