/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:32:57 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/16 17:38:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"

t_list	*add_obj_to_scene(t_scene *scene, t_object *obj)
{
	t_list	*elem;

	elem = ft_lstnew(obj);
	if (!elem)
		return (NULL);
	ft_lstadd_back(&scene->objs, elem);
	return (elem);
}

void	set_scene_light(t_scene *scene, t_3dpoint point, double ratio)
{
	scene->light.point = point;
	scene->light.ratio = ratio;
}
