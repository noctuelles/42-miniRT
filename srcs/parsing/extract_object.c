/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 18:03:37 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "minirt_lexer.h"
#include "scene.h"
#include "libft.h"
#include "tuple.h"
#include "parsing.h"
#include "define.h"

void	extract_sphere(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	double		diametre;
	uint32_t	color;
	t_object	*obj;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "invalid sphere center.", NULL);
	if (!extract_double_pos(lexer, &diametre))
		bad_exit_msg(minirt, "invalid sphere radius.", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "invalid sphere color.", NULL);
	obj = add_obj_to_scene(&minirt->scene, new_sphere(centre, diametre, color));
	if (!obj)
		bad_exit_msg(minirt, "sphere creation failed.", NULL);
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, O_SPHERE)))
		bad_exit_msg(minirt, "invalid sphere texture.", NULL);
}

void	extract_plan(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		vect;
	uint32_t	color;
	t_object	*obj;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "invalid plane position.", NULL);
	if (!extract_vector(lexer, &vect))
		bad_exit_msg(minirt, "invalid plane orientation.", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "invalid plane color.", NULL);
	obj = add_obj_to_scene(&minirt->scene, new_plan(centre, vect, color));
	if (!obj)
		bad_exit_msg(minirt, "plane creation failed.", NULL);
	obj->texture.type = TX_NONE;
}

void	extract_cylinder(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		orien;
	double		diam_haut[2];
	uint32_t	color;
	t_object	*obj;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "invalid cylinder center.", NULL);
	if (!extract_vector(lexer, &orien))
		bad_exit_msg(minirt, "invalid cylinder orientation.", NULL);
	if (!extract_double_pos(lexer, &diam_haut[0]))
		bad_exit_msg(minirt, "invalid cylinder radius.", NULL);
	if (!extract_double_pos(lexer, &diam_haut[1]))
		bad_exit_msg(minirt, "invalid cylinder height.", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "invalid cylinder color.", NULL);
	obj = add_obj_to_scene(&minirt->scene, new_cylinder(centre, diam_haut,
				orien, color));
	if (!obj)
		bad_exit_msg(minirt, "cone creation failed.", NULL);
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, O_CYLINDER)))
		bad_exit_msg(minirt, "invalid cylinder texture.", NULL);
}

void	extract_cone(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		orien;
	double		diam_haut[2];
	uint32_t	color;
	t_object	*obj;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "invalid cone center.", NULL);
	if (!extract_vector(lexer, &orien))
		bad_exit_msg(minirt, "invalid cone orientation.", NULL);
	if (!extract_double_pos(lexer, &diam_haut[0]))
		bad_exit_msg(minirt, "invalid cone radius.", NULL);
	if (!extract_double_pos(lexer, &diam_haut[1]))
		bad_exit_msg(minirt, "invalid cone height.", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "invalid cone color.", NULL);
	obj = add_obj_to_scene(&minirt->scene, new_cone(centre, diam_haut,
				orien, color));
	if (!obj)
		bad_exit_msg(minirt, "cone creation failed.", NULL);
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, O_CONE)))
		bad_exit_msg(minirt, "invalid cone texture.", NULL);
}
