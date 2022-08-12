/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_object2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:08:22 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 16:37:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "minirt_lexer.h"
#include "scene.h"
#include "libft.h"
#include "tuple.h"
#include "parsing.h"
#include "define.h"

void	extract_camera(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	double		fov;
	t_vec3		orien;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "invalid camera position.", NULL);
	if (!extract_vector_norm(lexer, &orien))
		bad_exit_msg(minirt, "invalid camera orientation", NULL);
	if (!extract_double_range(lexer, &fov, 0, 180))
		bad_exit_msg(minirt, "invalid camera fov", NULL);
	setup_camera(&minirt->camera, WIDTH, HEIGHT, fov);
	set_camera_view_matrix(&minirt->camera, centre, orien);
}

void	extract_light(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	double		ratio;
	uint32_t	color;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "invalid light position.", NULL);
	if (!extract_double_range(lexer, &ratio, 0, 1))
		bad_exit_msg(minirt, "invalid light ratio.", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "invalid light color.", NULL);
	if (!add_light_to_scene(&minirt->scene, centre, color, ratio))
		bad_exit_msg(minirt, "light creation failed.", NULL);
}

void	extract_ambiante_light(t_minirt *minirt, t_list **lexer)
{
	double		ratio;
	uint32_t	color;

	*lexer = (*lexer)->next;
	if (!extract_double_range(lexer, &ratio, 0, 1))
		bad_exit_msg(minirt, "invalid ambiant light ratio.", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "invalid ambiant light color.", NULL);
	set_ambiant_light(&minirt->scene, color, ratio);
}
