/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:47:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/07/30 15:51:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "minirt_struct.h"

/* object.c */

t_object	*new_sphere(t_point3 center, double radius, uint32_t color);
t_object	*new_plan(t_point3 point, t_vec3 normal, uint32_t color);
t_object	*new_cylinder(t_point3 pos, double diameter, double height, t_vec3 orientation,
		uint32_t color);
t_object	*ray_intersect_scene_objs(t_scene *scene, t_ray *ray,
		t_rayhit *rayhit);

/* scene.c */

t_object	*add_obj_to_scene(t_scene *scene, t_object *obj);
t_list		*add_light_to_scene(t_scene *scene, t_point3 pos, uint32_t color,
		double intensity);
void		set_ambiant_light(t_scene *scene, uint32_t color, double intensity);

/* shading.c */

t_color	get_shade(t_scene *scene, t_object *obj, t_rayhit *rayhit, t_ray *ray);

#endif
