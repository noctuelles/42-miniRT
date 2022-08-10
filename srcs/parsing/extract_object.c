/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 09:24:10 by bsavinel         ###   ########.fr       */
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
	
	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "Bad format for sphere");
	if (!extract_double_pos(lexer, &diametre))
		bad_exit_msg(minirt, "Bad format for sphere");
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Bad format for sphere");
	add_obj_to_scene(&minirt->scene, new_sphere(centre, diametre, color));
}

void	extract_plan(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		vect;
	uint32_t	color;
	
	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "Bad format for plan");
	if (!extract_vector(lexer, &vect))
		bad_exit_msg(minirt, "Bad format for plan");
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Bad format for plan");
	add_obj_to_scene(&minirt->scene, new_plan(centre, vect, color));
}

void	extract_cylinder(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	t_vec3		orien;
	double		hauteur;
	double		diametre;
	uint32_t	color;
	
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
	add_obj_to_scene(&minirt->scene, new_cylinder(centre, diametre, hauteur, orien, color));
}

void	extract_camera(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	double		fov;
	t_vec3		orien;
	
	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "Bad format for camera");
	if (!extract_vector_norm(lexer, &orien))
		bad_exit_msg(minirt, "Bad format for camera");
	if (!extract_double_range(lexer, &fov, 0, 180))
		bad_exit_msg(minirt, "Bad format for camera");
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
		bad_exit_msg(minirt, "Bad format for light");
	if (!extract_double_range(lexer, &ratio, 0, 1))
		bad_exit_msg(minirt, "Bad format for light");
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Bad format for light");
	add_light_to_scene(&minirt->scene, centre, color, ratio);
}

void	extract_ambiante_light(t_minirt *minirt, t_list **lexer)
{
	double		ratio;
	uint32_t	color;
	
	*lexer = (*lexer)->next;
	if (!extract_double_range(lexer, &ratio, 0, 1))
		bad_exit_msg(minirt, "Bad format for ambiante light");
	if (!extract_color(lexer, &color))
		bad_exit_msg(minirt, "Bad format for ambiante light");
	set_ambiant_light(&minirt->scene, color, ratio);
}