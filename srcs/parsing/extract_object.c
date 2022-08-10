/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 15:00:15 by bsavinel         ###   ########.fr       */
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
	
	printf("Sphere%d\n", D_BONUS);
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

void	extract_camera(t_minirt *minirt, t_list **lexer)
{
	t_point3	centre;
	double		fov;
	t_vec3		orien;
	
	*lexer = (*lexer)->next;
	if (!extract_point(lexer, &centre))
		bad_exit_msg(minirt, "1Bad format for camera");
	if (!extract_vector_norm(lexer, &orien))
		bad_exit_msg(minirt, "2Bad format for camera");
	if (!extract_double_range(lexer, &fov, 0, 180))
		bad_exit_msg(minirt, "3Bad format for camera");
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
	if(!add_light_to_scene(&minirt->scene, centre, color, ratio))
		bad_exit_msg(minirt, "Bad format for light");
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