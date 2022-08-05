/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:16:01 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/05 12:27:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "tuple.h"
#include "matrix.h"
#include "texture.h"
#include "scene.h"
#include "math_utils.h"
#include <math.h>

# define L_POWER 1.2e2

/* Using lambertian shading.
 * Note that i'm dividing by the distance square to get a more realistic
 * lightning.
 * I'm also dividing the light power by Pi to get a more rounded light. */

static inline void apply_diffuse_coeff(t_light *light, t_vec3 lightv,
		t_vec3 normal, t_color *color)
{
	double	dot;
	double	coeff;

	dot = max(0, vec_dot(vec_norm(lightv), normal));
	coeff = (L_POWER / M_PI) * light->intensity * dot / vec_mag_sqr(lightv);
	*color = tadd(*color, tmul_scalar(light->color, coeff));
}

static inline void	apply_specular_coeff(t_light *light, t_vec3 lightv,
		t_vec3 normal, t_vec3 eyev, t_color *color)
{
	t_vec3	reflectionv;
	double	factor;
	double	dot;

	reflectionv = get_reflection_vec(vec_norm(lightv), normal);
	dot = vec_dot(eyev, reflectionv);
	if (dot > 0)
	{
		factor = 30 * pow(dot, 50) / vec_mag_sqr(lightv) * light->intensity;
		*color = tadd(*color, tmul_scalar(vector(1, 1, 1), factor));
	}
}

static bool	is_a_shadow(t_scene *scene, t_rayhit const *f_rayhit,
		t_vec3 lightv, t_object *ofd)
{
	t_ray		ray;
	t_rayhit	rayhit;
	t_object	*obj;
	double		distance_to_light;

	ray.org = tadd(f_rayhit->intersect_p, tmul_scalar(f_rayhit->normal, 0.1));
	ray.dir = vec_norm(lightv);
	obj = ray_intersect_scene_objs(scene, &ray, &rayhit);
	if (obj)
	{
		distance_to_light = vec_mag_sqr(lightv);
		if (rayhit.t * rayhit.t < distance_to_light)
			return (true);
	}
	return (false);
}

static t_color	get_color_from_obj(t_object *obj, t_point3 intersect_p)
{
	if (obj->texture.texture_type == TX_CHECKER)
		return (get_checker_color(obj->texture, obj->uvmap_fnct(intersect_p)));
	else if (obj->texture.texture_type == TX_IMAGE)
		return (get_image_color(obj->texture, obj->uvmap_fnct(intersect_p)));
	else
		return (obj->albedo);
}

/* Loop through every light in the scene.
 * The diffuse coeffecient is applied before the loop. */

t_color	get_shade(t_scene *scene, t_object *obj, t_rayhit *rayhit, t_ray *ray)
{
	t_list	*elem;
	t_light	*light;
	t_color	pix_color;
	t_vec3	lightv;

	pix_color = tmul_scalar(scene->amb_light.color, scene->amb_light.intensity);
	elem = scene->light;
	while (elem)
	{
		light = elem->content;
		lightv = tsub(light->pos, rayhit->intersect_p);
		//if (is_a_shadow(scene, rayhit, lightv) && obj->type == T_CYLINDER)
		//	puts("woww");
		if (!is_a_shadow(scene, rayhit, lightv, obj))
		{
			apply_diffuse_coeff(light, lightv, rayhit->normal, &pix_color);
			apply_specular_coeff(light, lightv, rayhit->normal,
					tnegate(ray->dir), &pix_color);
		}
		elem = elem->next;
	}
	pix_color = tmul(pix_color, get_color_from_obj(obj,
				rayhit->intersect_p_local));
	return (pix_color);
}
