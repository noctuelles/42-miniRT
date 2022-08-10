/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:59:46 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 18:09:42 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include "define.h"
#include "end.h"
#include "renderer.h"
#include "multithreading.h"
#include "minirt_lexer.h"
#include "minirt_lexer.h"
#include <pthread.h>
#include <string.h>
#include "matrix.h"
#include "texture.h"
#include "scene.h"
#include "tuple.h"
#include "scene.h"
#include <math.h>
#include <stdio.h>
char *translate(t_token_type type)
{
	if (type == 0)
		return ("T_AMBIANT_LIGHT");
	if (type == 1)
		return ("T_CAMERA");
	if (type == 2)
		return ("T_LIGHT");
	if (type == 3)
		return ("T_SPHERE");
	if (type == 4)
		return ("T_PLAN");
	if (type == 5)
		return ("T_CYLINDER");
	if (type == 6)
		return ("T_VALUE");
	if (type == 7)
		return ("T_NEWLINE");
	if (type == 8)
		return ("T_COMMA");
	if (type == 9)
		return ("T_BREAK");
	if (type == 10)
		return ("T_NULL");
	if (type == 11)
		return ("T_CONE");
	return ("NULL");
}
void	print_tokens(t_list *tkns)
{
	for (t_list *elem = tkns; elem; elem = elem->next)
	{
		t_token *tkn = elem->content;
		printf("<%s> ", translate(tkn->type));
		if (tkn->type == T_NEWLINE)
			printf("\n");
	}
}
int	main(int ac, char **av)
{
	t_minirt	minirt;
	memset(&minirt, 0, sizeof(t_minirt));

	(void) ac;
	(void)av;

	t_object	*cobj;
	//t_list	*tkns = lex_from_file(av[1]);
	/*if (!tkns)
		return (1);
	else
	{
		print_tokens(tkns);
		return (0);
	}*/
	if (!init_mlx_struct(&minirt.mlx))
		return (1);

	t_texture	skybox, moon, sun, earth;
	create_image_texture(minirt.mlx.ptr, &skybox, "textures/stars.xpm");
	create_image_texture(minirt.mlx.ptr, &moon, "textures/moon.xpm");
	create_image_texture(minirt.mlx.ptr, &sun, "textures/sun.xpm");
	create_image_texture(minirt.mlx.ptr, &earth, "textures/earth.xpm");
	apply_normal_map_to_texture(minirt.mlx.ptr, &moon, "textures/moon_normal_map.xpm" );
	apply_normal_map_to_texture(minirt.mlx.ptr, &sun, "textures/sun_normal_map.xpm" );
	apply_normal_map_to_texture(minirt.mlx.ptr, &earth, "textures/earth_normal_map.xpm" );

	cobj = add_obj_to_scene(&minirt.scene, new_sphere(point(0, 0, 0), 6, 0x00FFFF));
	apply_obj_texture(cobj, skybox);
	cobj = add_obj_to_scene(&minirt.scene, new_sphere(point(4, 2, 3.5), 0.7, 0x00FFFF));
	apply_obj_texture(cobj, moon);
	cobj = add_obj_to_scene(&minirt.scene, new_sphere(point(-4, 2, 5.5), 1.7, 0x00FFFF));
	apply_obj_texture(cobj, sun);
	cobj = add_obj_to_scene(&minirt.scene, new_sphere(point(1, -0.5, 4), 1.5, 0x00FFFF));
	apply_obj_texture(cobj, earth);

	//cobj = add_obj_to_scene(&minirt.scene, new_cone(point(-1, 3.4, 7), 0.7, 2, vector(0, 1, 0), 0xff00ff));



	/*cobj = add_obj_to_scene(&minirt.scene, new_sphere(point(0, 1, 8), 1, 0x00FF00));
	cobj = add_obj_to_scene(&minirt.scene, new_sphere(point(2, 3, 8), 1, 0x00FF00));
	cobj = add_obj_to_scene(&minirt.scene, new_sphere(point(-2, 3, 8), 1, 0x00FF00));

	cobj = add_obj_to_scene(&minirt.scene, new_plan(point(0, -1, 0), vector(0, 1, 0.0), 0xffffff));
	apply_obj_texture(cobj, create_checkered_texture(4, 4, 0x00FFFF, 0xFFFFFF));

	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(0, 0.0, 8), 0.6, 4, vector(0, 1, 0), 0x00ffff));
	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(1, 2.0, 8), 0.5, 4, vector(1, 1, 0), 0x00ffff));
	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(-1, 2.0, 8), 0.5, 4, vector(-1, 1, 0), 0x00ffff));

	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(2, 0.0, 8), 0.5, 9, vector(0, 1, 0), 0xff00ff));
	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(-2, 0.0, 8), 0.5, 9, vector(0, 1, 0), 0xff00ff));

	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(5.5, 0.0, 8), 0.5, 39, vector(-1, 1, 0), 0xff00ff));
	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(-5.5, 0.0, 8), 0.5, 39, vector(1, 1, 0), 0xff00ff));*/

	add_light_to_scene(&minirt.scene, point(0, 0, 0), 0xffffff, 1);
	set_ambiant_light(&minirt.scene, 0xFFFFFF, 0.2);


	setup_workers(&minirt);
	setup_camera(&minirt.camera, WIDTH, HEIGHT, FOV_ANGLE);
	set_camera_view_matrix(&minirt.camera, point(0, 0, 0), vector(0, 0, 1));
	render_img(&minirt);
	launch_loop(&minirt);

	return (0);
}
