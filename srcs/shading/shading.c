/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:16:01 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/06 16:49:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "tuple.h"
#include "matrix.h"
#include "texture.h"
#include "scene.h"
#include "math_utils.h"
#include <math.h>
#include <string.h>

# define L_POWER 1.2e2

/* Using lambertian shading.
 * Note that i'm dividing by the distance square to get a more realistic
 * lightning.
 * I'm also dividing the light power by Pi to get a more rounded light. */

static inline void	apply_lightning(t_light *light, t_rayhit *rayhit)
{
	t_vec3	reflectionv;
	double	factor;
	double	coeff;
	double	dot;

	dot = max(0, vec_dot(vec_norm(rayhit->lightv), rayhit->normal));
	coeff = (L_POWER / M_PI) * light->intensity * dot /
		vec_mag_sqr(rayhit->lightv);
	rayhit->pcolor = tadd(rayhit->pcolor, tmul_scalar(light->color, coeff));
	reflectionv = get_reflection_vec(vec_norm(rayhit->lightv), rayhit->normal);
	dot = vec_dot(rayhit->eyev, reflectionv);
	if (dot > 0)
	{
		factor = 30 * pow(dot, 50) / vec_mag_sqr(rayhit->lightv)
			* light->intensity;
		rayhit->pcolor = tadd(rayhit->pcolor,
				tmul_scalar(vector(1, 1, 1), factor));
	}
}

static bool	is_a_shadow(t_scene *scene, t_rayhit *f_rayhit)
{
	t_ray		ray;
	t_rayhit	rayhit;
	t_object	*obj;
	double		distance_to_light;

	ray.org = tadd(f_rayhit->intersect_p, tmul_scalar(f_rayhit->normal, 0.1));
	ray.dir = vec_norm(f_rayhit->lightv);
	obj = ray_intersect_scene_objs(scene, &ray, &rayhit);
	if (obj)
	{
		distance_to_light = vec_mag_sqr(f_rayhit->lightv);
		if (rayhit.t * rayhit.t < distance_to_light)
			return (true);
	}
	return (false);
}

static t_color	get_color_from_obj(t_object *obj, t_rayhit *rayhit)
{
	if (obj->texture.texture_type == TX_CHECKER)
		return (get_checker_color(obj->texture, rayhit->uv));
	else if (obj->texture.texture_type >= TX_IMAGE)
		return (get_image_color(obj->texture, rayhit->uv));
	else
		return (obj->albedo);
}

/* Loop through every light in the scene.
 * The diffuse coeffecient is applied before the loop. */

t_color	get_shade(t_scene *scene, t_object *obj, t_rayhit *rayhit)
{
	t_list	*elem;
	t_light	*light;

	rayhit->pcolor = tmul_scalar(scene->amb_light.color,
			scene->amb_light.intensity);
	elem = scene->light;
	if (obj->texture.texture_type != TX_NONE)
	{
		rayhit->uv = obj->uvmap_fnct(rayhit->intersect_p_local);
		if (obj->texture.texture_type == TX_IMAGEW_NMAP)
			perturb_normal(obj->texture, rayhit);
	}
	while (elem)
	{
		light = elem->content;
		rayhit->lightv = tsub(light->pos, rayhit->intersect_p);
		if (!is_a_shadow(scene, rayhit))
			apply_lightning(light, rayhit);
		elem = elem->next;
	}
	return (tmul(rayhit->pcolor, get_color_from_obj(obj, rayhit)));
}
