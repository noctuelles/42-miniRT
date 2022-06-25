/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:16:01 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 23:34:54 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "tuple.h"
#include "texture.h"
#include "scene.h"
#include "math_utils.h"

# define L_POWER 2.5e2

static inline void apply_diffuse_coeff(t_light *light, t_vec3 lightv,
		t_vec3 normal, t_color *color)
{
	double	dot;
	double	coeff;

	dot = max(0, vec_dot(vec_norm(lightv), normal));
	coeff = L_POWER * light->intensity * dot / vec_mag_sqr(lightv);
	*color = tadd(*color, tmul_scalar(light->color, coeff));
}

static bool	is_a_shadow(t_scene *scene, t_rayhit const *f_rayhit,
		t_vec3 lightv)
{
	t_ray		ray;
	t_rayhit	rayhit;
	t_object	*obj;
	double		distance_to_light;

	ray.org = tadd(f_rayhit->intersect_p, tmul_scalar(f_rayhit->normal, 1e-9));
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
	else
		return (obj->albedo);
}

t_color	get_shade(t_scene *scene, t_object *obj, t_rayhit *rayhit)
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
		if (!is_a_shadow(scene, rayhit, lightv))
		{
			apply_diffuse_coeff(light, lightv, rayhit->normal, &pix_color);
		}
		elem = elem->next;
	}
	pix_color = tmul(pix_color, get_color_from_obj(obj, rayhit->intersect_p));
	return (pix_color);
}
