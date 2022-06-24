/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:47:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/24 18:29:19 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "minirt_struct.h"

/* object.c */

t_object	*new_sphere(t_point3 center, double radius, uint32_t color);
t_object	*new_plan(t_point3 point, t_vec3 normal, uint32_t color);
t_object	*ray_intersect_scene_objs(t_scene *scene, t_ray *ray,
		t_rayhit *rayhit);

/* scene.c */

t_list		*add_obj_to_scene(t_scene *scene, t_object *obj);
void		set_scene_light(t_scene *scene, t_point3 point, double ratio);
void	apply_obj_transform(t_object *obj, t_matrix4 const M);

#endif
