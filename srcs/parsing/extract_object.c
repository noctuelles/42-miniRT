/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 15:38:19 by bsavinel         ###   ########.fr       */
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
		bad_exit_msg(minirt, "Invalid center for sphere", NULL);
	if (!extract_double_pos(lexer, &diametre))
		bad_exit_msg(minirt, "Invalid radius sphere", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Invalid color for sphere", NULL);
	obj = add_obj_to_scene(&minirt->scene, new_sphere(centre, diametre, color));
	if (!obj)
		bad_exit_msg(minirt, "Creation of sphere failed", NULL);
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, O_SPHERE)))
		bad_exit_msg(minirt, "Texture for sphere failed", NULL);
}

void	extract_plan(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		vect;
	uint32_t	color;
	t_object	*obj;

	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "Invalid point for plane", NULL);
	if (!extract_vector(lexer, &vect))
		bad_exit_msg(minirt, "Invalid vector for plane", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Invalid color for plane", NULL);
	obj = add_obj_to_scene(&minirt->scene, new_plan(centre, vect, color));
	if (!obj)
		bad_exit_msg(minirt, "Creation of plane failed", NULL);
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, O_PLAN)))
		bad_exit_msg(minirt, "Texture for plane failed", NULL);
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
		bad_exit_msg(minirt, "Invalid center for cylinder", NULL);
	if (!extract_vector(lexer, &orien))
		bad_exit_msg(minirt, "Invalid vector for cylinder", NULL);
	if (!extract_double_pos(lexer, &diam_haut[0]))
		bad_exit_msg(minirt, "Invalid radius for cylinder", NULL);
	if (!extract_double_pos(lexer, &diam_haut[1]))
		bad_exit_msg(minirt, "Invalid height for cylinder", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Invalid color for cylinder", NULL);
	obj = add_obj_to_scene(&minirt->scene, new_cylinder(centre, diam_haut[0],
				diam_haut[1], orien, color));
	if (!obj)
		bad_exit_msg(minirt, "Creation of cylinde failed", NULL);
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, O_CYLINDER)))
		bad_exit_msg(minirt, "Texture for cylinde failed", NULL);
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
		bad_exit_msg(minirt, "Invalid center for cone", NULL);
	if (!extract_vector(lexer, &orien))
		bad_exit_msg(minirt, "Invalid orientaion for cone", NULL);
	if (!extract_double_pos(lexer, &diam_haut[0]))
		bad_exit_msg(minirt, "Invalid Radius for cone", NULL);
	if (!extract_double_pos(lexer, &diam_haut[1]))
		bad_exit_msg(minirt, "Invalid height for cone", NULL);
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Invalid color for cone", NULL);
	obj = add_obj_to_scene(&minirt->scene, new_cone(centre, diam_haut[0],
				diam_haut[1], orien, color));
	if (!obj)
		bad_exit_msg(minirt, "Creation of cone failed", NULL);
	obj->texture.type = TX_NONE;
	if (D_BONUS && !(extract_texture(minirt, lexer, obj, O_CONE)))
		bad_exit_msg(minirt, "Texture for cone failed", NULL);
}
