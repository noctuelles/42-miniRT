/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 15:30:44 by bsavinel         ###   ########.fr       */
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
		bad_exit_msg(minirt, "Bad format for sphere");
	if (!extract_double_pos(lexer, &diametre))
		bad_exit_msg(minirt, "Bad format for sphere");
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Bad format for sphere");
	obj = add_obj_to_scene(&minirt->scene, new_sphere(centre, diametre, color));
	if (!obj)
		bad_exit_msg(minirt, "Bad format for plan");
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, 8, 8)))
		bad_exit_msg(minirt, "Bad format for cone");
}

void	extract_plan(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		vect;
	uint32_t	color;
	t_object	*obj;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "Bad format for plan");
	if (!extract_vector(lexer, &vect))
		bad_exit_msg(minirt, "Bad format for plan");
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Bad format for plan");
	obj = add_obj_to_scene(&minirt->scene, new_plan(centre, vect, color));
	if (!obj)
		bad_exit_msg(minirt, "Bad format for plan");
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, 4, 4)))
		bad_exit_msg(minirt, "Bad format for cone");
}

void	extract_cylinder(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		orien;
	double		hauteur;
	double		diametre;
	uint32_t	color;
	t_object	*obj;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "Bad format for cylinder");
	if (!extract_vector(lexer, &orien))
		bad_exit_msg(minirt, "Bad format for cylinder");
	if (!extract_double_pos(lexer, &diametre))
		bad_exit_msg(minirt, "Bad format for cylinder");
	if (!extract_double_pos(lexer, &hauteur))
		bad_exit_msg(minirt, "Bad format for cylinder");
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Bad format for cylinder");
	obj = add_obj_to_scene(&minirt->scene, new_cylinder(centre, diametre, hauteur, orien, color));
	if (!obj)
		bad_exit_msg(minirt, "Bad format for plan");
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, 16, 8)))
		bad_exit_msg(minirt, "Bad format for cone");
}

void	extract_cone(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		orien;
	double		diametre;
	double		hauteur;
	uint32_t	color;
	t_object	*obj;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "Bad format for cone");
	if (!extract_vector(lexer, &orien))
		bad_exit_msg(minirt, "Bad format for cone");
	if (!extract_double_pos(lexer, &diametre))
		bad_exit_msg(minirt, "Bad format for cone");
	if (!extract_double_pos(lexer, &hauteur))
		bad_exit_msg(minirt, "Bad format for cone");
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Bad format for cone");
	obj = add_obj_to_scene(&minirt->scene, new_cone(centre, diametre, hauteur, orien, color));
	if (!obj)
		bad_exit_msg(minirt, "Bad format for plan");
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, 16, 8)))
		bad_exit_msg(minirt, "Bad format for cone");
}
