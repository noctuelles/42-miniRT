/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:50:45 by plouvel           #+#    #+#             */
/*   Updated: 2022/12/13 16:02:16 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_bonus.h"
#include "tuple_bonus.h"
#include <math.h>

/* build_view_matrix build the view matrix with a given origine and a
 * "look" vector that describe the orientation of the camera. */

static inline t_matrix4	build_view_matrix(t_minirt* minirt, t_point3 org, t_vec3 look)
{
	t_matrix4	transform;

	look = vec_norm(look);
	minirt->camera.alpha = atan2(look.x, look.z);
	minirt->camera.beta = atan2(look.y, sqrt(look.x * look.x + look.z * look.z));
	transform = matrix4_rotate_x(-minirt->camera.beta);
	transform = matrix4_mul(matrix4_rotate_y(minirt->camera.alpha), transform);
	transform = matrix4_mul(matrix4_translate(org.x, org.y, org.z), transform);
	return (transform);
}

void	setup_camera(t_camera *camera, size_t width, size_t height, double fov)
{
	camera->aspect_ratio = (double) width / height;
	camera->scalar_fov = tan(((fov / 2) * M_PI) / 180);
	camera->screen_width = width;
	camera->screen_height = height;
}

/* generate_ray creates a ray from the position in screen space.
 * The ray in camera space is transformed in world space using the camera
 * view matrx. */

void	generate_ray(t_camera *camera, t_ray *ray, t_rayhit *rayhit,
		t_point2 *rp)
{
	double	px;
	double	py;

	px = (2 * ((rp->x + 0.5) / camera->screen_width) - 1)
		* camera->scalar_fov * camera->aspect_ratio;
	py = (1 - 2 * ((rp->y + 0.5) / camera->screen_height)) * camera->scalar_fov;
	ray->org = matrix4_tmul(camera->transform, point(0, 0, 0));
	ray->dir = vec_norm(matrix4_tmul(camera->transform, vector(px, py, 1)));
	rayhit->eyev = tnegate(ray->dir);
}

void	set_camera_view_matrix(t_minirt *minirt, t_point3 org, t_vec3 look)
{
	minirt->camera.from = org;
	minirt->camera.look = look;
	minirt->camera.transform = build_view_matrix(minirt, org, look);
}

void	set_camera_view_matrix_angle(t_minirt *minirt, t_point3 org)
{
	t_matrix4	transform;

	transform = matrix4_rotate_x(-minirt->camera.beta);
	transform = matrix4_mul(matrix4_rotate_y(minirt->camera.alpha), transform);
	transform = matrix4_mul(matrix4_translate(org.x, org.y, org.z), transform);
	minirt->camera.from = org;
	minirt->camera.transform = transform;
}
