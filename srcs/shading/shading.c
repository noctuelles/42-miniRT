/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:16:01 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/10 14:48:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "tuple.h"
#include "matrix.h"
#include "texture.h"
#include "scene.h"
#include "math_utils.h"
#include "define.h"
#include <math.h>
#include <string.h>

/* Using lambertian shading.
 * Note that i'm dividing by the distance square to get a more realistic
 * lightning.
 * I'm also dividing the light power by Pi to get a more rounded light. */

static inline void	apply_lightning(t_object_type obj_type, t_light *light,
		t_rayhit *rayhit)
{
	t_vec3	reflectionv;
	double	factor;
	double	coeff;
	double	dot;

	reflectionv = get_reflection_vec(rayhit->nlightv, rayhit->normal);
	dot = vec_dot(rayhit->eyev, reflectionv);
	if (dot > 0 && obj_type != O_PLAN)
	{
		factor = 30 * pow(dot, 50) / rayhit->mag_sqr_lightv * light->intensity;
		rayhit->pcolor.x += factor;
		rayhit->pcolor.y += factor;
		rayhit->pcolor.z += factor;
	}
	dot = max(0, vec_dot(rayhit->nlightv, rayhit->normal));
	coeff = (L_POWER / M_PI) * light->intensity * dot / rayhit->mag_sqr_lightv;
	rayhit->pcolor = tadd(rayhit->pcolor, tmul_scalar(light->color, coeff));
}

static inline bool	is_a_shadow(t_scene *scene, t_rayhit *f_rayhit)
{
	t_ray		ray;
	t_rayhit	rayhit;
	t_object	*obj;
	double		distance_to_light;

	ray.org = tadd(f_rayhit->intersect_p, tmul_scalar(f_rayhit->normal,
				EPSILON));
	ray.dir = f_rayhit->nlightv;
	obj = ray_intersect_scene_objs(scene, &ray, &rayhit);
	if (obj)
	{
		distance_to_light = f_rayhit->mag_sqr_lightv;
		if (rayhit.t * rayhit.t < distance_to_light)
			return (true);
	}
	return (false);
}

static inline t_color	get_color_from_obj(t_object *obj, t_rayhit *rayhit)
{
	if (obj->texture.type == TX_CHECKER)
		return (get_checker_color(obj->texture, rayhit->uv));
	else if (obj->texture.type >= TX_IMAGE)
		return (get_image_color(obj->texture, rayhit->uv));
	else
		return (obj->albedo);
}

static inline void	pre_compute(t_light *light, t_rayhit *rayhit)
{
	rayhit->lightv = tsub(light->pos, rayhit->intersect_p);
	rayhit->nlightv = vec_norm(rayhit->lightv);
	rayhit->mag_sqr_lightv = vec_mag_sqr(rayhit->lightv);
}

/* Loop through every light in the scene.
 * The diffuse coeffecient is applied before the loop. */

t_color	get_shade(t_scene *scene, t_object *obj, t_rayhit *rayhit)
{
	t_list	*elem;
	t_light	*light;

	if (obj->texture.type != TX_NONE)
	{
		rayhit->uv = obj->uvmap_fnct(rayhit->intersect_p_local);
		if (obj->texture.type == TX_IMAGEW_NMAP)
			perturb_normal(obj->texture, rayhit);
	}
	rayhit->pcolor = tmul_scalar(scene->amb_light.color,
			scene->amb_light.intensity);
	if (vec_dot(rayhit->eyev, rayhit->normal) < 0)
		rayhit->normal = tnegate(rayhit->normal);
	elem = scene->light;
	while (elem)
	{
		light = elem->content;
		pre_compute(light, rayhit);
		if (!is_a_shadow(scene, rayhit))
			apply_lightning(obj->type, light, rayhit);
		elem = elem->next;
	}
	return (tmul(rayhit->pcolor, get_color_from_obj(obj, rayhit)));
}
