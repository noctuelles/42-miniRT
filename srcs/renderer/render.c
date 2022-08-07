/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:52:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/07 14:12:45 by plouvel          ###   ########.fr       */
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
#include "multithreading.h"
#include <limits.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

t_matrix4	transform(t_vec3 from, t_vec3 forward)
{
	t_matrix4	M;
	t_vec3	left;
	t_vec3	true_up;

	left = vec_cross(forward, vector(0, 1, 0));
	if (vec_mag(left) == 0)
		left = vec_cross(forward, vector(0, 0, 1));
	left = vec_norm(left);
	true_up = vec_norm(vec_cross(left, forward));
	M.m[0][0] = left.x;
	M.m[0][1] = left.y;
	M.m[0][2] = left.z;

	M.m[1][0] = true_up.x;
	M.m[1][1] = true_up.y;
	M.m[1][2] = true_up.z;

	M.m[2][0] = -forward.x;
	M.m[2][1] = -forward.y;
	M.m[2][2] = -forward.z;

	M.m[3][3] = 1.;

	return (matrix4_mul(M, matrix4_translate(-from.x, -from.y, -from.z)));
}

static t_matrix4	build_view_matrix(t_vec3 orient)
{
	t_matrix4	transform;
	double		alpha;
	double		beta;

	orient = vec_norm(orient);
	alpha = atan2(orient.x, orient.z);
	beta = atan2(orient.y, sqrt(orient.x * orient.x + orient.z * orient.z));
	transform = matrix4_rotate_x(-beta);
	transform = matrix4_mul(matrix4_rotate_y(alpha), transform);
	printf("alpha : %f\n", alpha * 180 / M_PI);
	printf("beta : %f\n", beta * 180 / M_PI);
	return (transform);
}

static inline void	generate_ray(t_ray *ray, t_rayhit *rayhit, t_point3 viewport_point, t_matrix4 m)
{
	ray->org = point(0, 0, 2);
	ray->dir = vec_norm(matrix4_tmul(m, viewport_point));
	ray->dir.w = 0;
	rayhit->eyev = tnegate(ray->dir);
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

static uint32_t	get_color(t_color color)
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

t_matrix4	build_rotation_from_dir_vec(t_vec3 forward);

void	setup_scene()
{

}


void	render_img(t_minirt *minirt)
{
	t_point3	viewport_point;
	t_matrix4	vmatrix;
	t_ray		ray;
	t_camera	camera;
	t_rayhit	rayhit;
	size_t		i;
	t_object	*cobj;
	size_t		j;

	camera = new_camera(WIDTH, HEIGHT, FOV);
	vmatrix = build_view_matrix(vector(0, 0, 1));
	printf("-- Camera information --\n");
	printf("Half_width : %f\n", camera.half_width);
	printf("Half_height : %f\n", camera.half_height);
	printf("pixel_size : %f\n", camera.pixel_size);

	print_matrix4(vmatrix);
	//cobj = add_obj_to_scene(&minirt->scene, new_sphere(point(0, 1, 4), 1, 0x00FF00));
	//apply_obj_texture(cobj, create_checkered_texture(10, 10, 0xFF00FF, 0xFFFF00));


	cobj = add_obj_to_scene(&minirt->scene, new_sphere(point(0, 1, 8), 1, 0x00FF00));
	cobj = add_obj_to_scene(&minirt->scene, new_sphere(point(2, 3, 8), 1, 0x00FF00));
	cobj = add_obj_to_scene(&minirt->scene, new_sphere(point(-2, 3, 8), 1, 0x00FF00));

	cobj = add_obj_to_scene(&minirt->scene, new_plan(point(0, -1, 0), vector(0, 1, -0.01), 0xffffff));
	apply_obj_texture(cobj, create_checkered_texture(4, 4, 0x00FFFF, 0xFFFFFF));
	cobj = add_obj_to_scene(&minirt->scene, new_plan(point(0, 5, 0), vector(0.0, -1, 0), 0xffffff));
	apply_obj_texture(cobj, create_checkered_texture(4, 4, 0x00FFFF, 0xFFFFFF));

	cobj = add_obj_to_scene(&minirt->scene, new_cylinder(point(0, 0.0, 8), 0.6, 4, vector(0, 1, 0), 0x00ffff));
	cobj = add_obj_to_scene(&minirt->scene, new_cylinder(point(1, 2.0, 8), 0.5, 4, vector(1, 1, 0), 0x00ffff));
	cobj = add_obj_to_scene(&minirt->scene, new_cylinder(point(-1, 2.0, 8), 0.5, 4, vector(-1, 1, 0), 0x00ffff));

	cobj = add_obj_to_scene(&minirt->scene, new_cylinder(point(2, 0.0, 8), 0.5, 9, vector(0, 1, 0), 0xff00ff));
	cobj = add_obj_to_scene(&minirt->scene, new_cylinder(point(-2, 0.0, 8), 0.5, 9, vector(0, 1, 0), 0xff00ff));

	cobj = add_obj_to_scene(&minirt->scene, new_cylinder(point(5.5, 0.0, 8), 0.5, 39, vector(-1, 1, 0), 0xff00ff));
	cobj = add_obj_to_scene(&minirt->scene, new_cylinder(point(-5.5, 0.0, 8), 0.5, 39, vector(1, 1, 0), 0xff00ff));


	add_light_to_scene(&minirt->scene, point(0,3, 0), 0xFFFFFF, 1);
	set_ambiant_light(&minirt->scene, 0xFFFFFF, 0.1);

	struct timeval	t, t1;
	setup_workers(minirt);
	gettimeofday(&t, NULL);
	launch_workers(minirt);

	/*viewport_point.z = WIDTH / (2 * tan(FOV / 2));
	i = 0;

	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			t_object	*obj;

			viewport_point.x = j - (WIDTH / 2.0);
			viewport_point.y = i - (HEIGHT / 2.0);
			generate_ray(&ray, &rayhit, viewport_point, vmatrix);
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
	gettimeofday(&t1, NULL);
	mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win, minirt->mlx.img.img, 0, 0);
	*/
	gettimeofday(&t1, NULL);
	printf("Rendered in %lu mlsec.\n", get_mlsec_time(t1) - get_mlsec_time(t));
mlx_put_image_to_window(minirt->mlx.ptr, minirt->mlx.win, minirt->mlx.img.img, 0, 0);
	puts("Rendering done");
}
