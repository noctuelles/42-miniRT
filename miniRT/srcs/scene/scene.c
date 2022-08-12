/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:32:57 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 14:45:07 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "mlx_utils.h"
#include "tuple.h"
#include <stdlib.h>

t_object	*add_obj_to_scene(t_scene *scene, t_object *obj)
{
	t_list	*elem;

	elem = ft_lstnew(obj);
	if (!elem)
		return (NULL);
	ft_lstadd_back(&scene->objs, elem);
	return (obj);
}

t_list	*add_light_to_scene(t_scene *scene, t_point3 pos, uint32_t color,
		double intensity)
{
	t_list	*elem;
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->pos = pos;
	light->intensity = intensity;
	light->color = get_norm_color(color);
	elem = ft_lstnew(light);
	if (!elem)
	{
		free(light);
		return (NULL);
	}
	ft_lstadd_back(&scene->light, elem);
	return (elem);
}

void	set_ambiant_light(t_scene *scene, uint32_t color, double intensity)
{
	scene->amb_light.color = get_norm_color(color);
	scene->amb_light.intensity = intensity;
	scene->amb_light.pos = point(0, 0, 0);
}

/* If the spectified ray hit an object in the specified scene, return the first
 * object hitted and fill the rayhit structure. */

t_object	*ray_intersect_scene_objs(t_scene *scene, t_ray *ray,
		t_rayhit *rayhit)
{
	t_list		*elem;
	t_object	*obj;
	t_object	*closest_obj;
	t_rayhit	closest_rayhit;

	elem = scene->objs;
	closest_obj = NULL;
	while (elem)
	{
		obj = elem->content;
		if (obj->fnct(obj, ray, rayhit))
		{
			if (!closest_obj || rayhit->t < closest_rayhit.t)
			{
				closest_rayhit = *rayhit;
				closest_obj = obj;
			}
		}
		elem = elem->next;
	}
	*rayhit = closest_rayhit;
	return (closest_obj);
}
