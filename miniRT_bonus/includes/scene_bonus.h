/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:47:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 13:36:26 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include "minirt_struct.h"

/* object.c */

t_object	*new_sphere(t_point3 center, double radius, uint32_t color);
t_object	*new_plan(t_point3 point, t_vec3 normal, uint32_t color);
t_object	*new_cylinder(t_point3 pos, double diam_heig[2],
				t_vec3 orientation, uint32_t color);
t_object	*new_cone(t_point3 pos, double diam_heig[2],
				t_vec3 orient, uint32_t color);
t_object	*ray_intersect_scene_objs(t_scene *scene, t_ray *ray,
				t_rayhit *rayhit);

/* object2.c */

t_matrix4	build_rotation_matrix(t_vec3 orient);
void		apply_obj_transform(t_object *obj, t_matrix4 const M);

/* scene.c */

t_object	*add_obj_to_scene(t_scene *scene, t_object *obj);
t_list		*add_light_to_scene(t_scene *scene, t_point3 pos, uint32_t color,
				double intensity);
void		set_ambiant_light(t_scene *scene, uint32_t color, double intensity);

/* shading.c */

t_color		get_shade(t_scene *scene, t_object *obj, t_rayhit *rayhit);
void		perturb_normal(t_texture texture, t_rayhit *rayhit);

/* camera.c */

void		setup_camera(t_camera *camera, size_t width, size_t height,
				double fov);
void		set_camera_view_matrix(t_camera *camera, t_point3 from,
				t_vec3 look);
void		generate_ray(t_camera *camera, t_ray *ray, t_rayhit *rayhit,
				t_point2 *rp);

#endif
