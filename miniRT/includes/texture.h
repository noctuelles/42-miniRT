/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:11:16 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/11 16:56:05 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "minirt_struct.h"

/* uv_mapping.c */

t_uv		get_planar_map(t_point3 intersect_p);
t_uv		get_spherical_map(t_point3 intersect_p);
t_uv		get_cylinder_map(t_point3 intersect_p);
t_uv		get_cone_map(t_point3 intersect_p);

/* texture.c */

t_color		get_image_color(t_texture texture, t_uv uv);
t_vec3		get_image_normal(t_texture texture, t_uv uv);

t_texture	*create_image_texture(void *mlx, t_texture *texture,
				const char *path);
t_texture	*apply_normal_map_to_texture(void *mlx, t_texture *texture,
				const char *path);

t_texture	create_checkered_texture(int width, int height, uint32_t a,
				uint32_t b);
t_color		get_checker_color(t_texture texture, t_uv uv);
void		apply_obj_texture(t_object *obj, t_texture texture);

#endif
