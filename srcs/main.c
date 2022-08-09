/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:59:46 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/09 16:51:17 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include "define.h"
#include "parsing.h"
#include "end.h"
#include "renderer.h"
#include "multithreading.h"
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

int	main(int ac, char **av)
{
	t_minirt	minirt;
	memset(&minirt, 0, sizeof(t_minirt));

	(void) ac;
	(void)av;

	t_object	*cobj;
	/*t_list	*tkns = lex_from_file(av[1]);
	if (!tkns)
		return (1);*/
	if (ac != 2)
	{
		printf("Error\nBad numeber of argument\n");
		return (1);
	}
	parser(&minirt, av[1]);
	if (!init_mlx_struct(&minirt.mlx))
		return (1);

	/*t_texture texture;
	create_image_texture(minirt.mlx.ptr, &texture, "textures/moon.xpm");
	t_texture	skybox;
	create_image_texture(minirt.mlx.ptr, &skybox, "textures/stars.xpm");
	apply_normal_map_to_texture(minirt.mlx.ptr, &texture, "textures/moon_nmap.xpm");

	cobj = add_obj_to_scene(&minirt.scene, new_plan(point(0, -1, 0), vector(0, 1, 0.0), 0xffffff));
	cobj = add_obj_to_scene(&minirt.scene, new_cone(point(4, 0, 5), 2, 4, vector(0, 1, 0.), 0x00ffff));
	apply_obj_texture(cobj, create_checkered_texture(16, 8, 0xFF0000, 0xFFFFFF));
	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(0, 0.0, 5), 1, 3, vector(0, 1, 0), 0x00ffff));
	apply_obj_texture(cobj, create_checkered_texture(16, 2, 0x00FFFF, 0xFFFFFF));

	cobj = add_obj_to_scene(&minirt.scene, new_sphere(point(0, 1, 8), 1, 0x00FF00));
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
	cobj = add_obj_to_scene(&minirt.scene, new_cylinder(point(-5.5, 0.0, 8), 0.5, 39, vector(1, 1, 0), 0xff00ff));

	add_light_to_scene(&minirt.scene, point(0,2, 0), 0xFFFFFF, 0.5);
	set_ambiant_light(&minirt.scene, 0xFFFFFF, 0.15);*/

	setup_workers(&minirt);
	//setup_camera(&minirt.camera, WIDTH, HEIGHT, FOV_ANGLE);
	//set_camera_view_matrix(&minirt.camera, point(-2, 3, 0), vector(1, -.5, 1));
	render_img(&minirt);
	launch_loop(&minirt);

	return (0);
}
