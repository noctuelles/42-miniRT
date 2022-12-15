/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_loop_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:16:24 by bsavinel          #+#    #+#             */
/*   Updated: 2022/12/14 18:18:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils_bonus.h"
#include "minirt_struct_bonus.h"
#include "end_bonus.h"
#include "define_bonus.h"
#include "renderer_bonus.h"
#include "scene_bonus.h"
#include "matrix_bonus.h"
#include "mlx.h"
#include "tuple_bonus.h"
#include <stdio.h>
#include <math.h>

static int	key_press(int keycode, t_minirt* minirt)
{
	switch (keycode)
	{
		case D_ESCAPE:
			good_exit(minirt);
			break;
		case D_Z:
			minirt->camera.from = tadd(minirt->camera.from, tmul_scalar(minirt->camera.look, 0.5));
			break;
		case D_S:
			minirt->camera.from = tadd(minirt->camera.from, tmul_scalar(minirt->camera.look, -0.5));
			break;
		case D_Q:
			{
				t_vec3 p = vec_norm(vec_cross(vector(0, 1, 0), minirt->camera.look));
				minirt->camera.from = tadd(minirt->camera.from, tmul_scalar(p, -0.5));
			}
			break;
		case D_D:
			{
				t_vec3 p = vec_norm(vec_cross(vector(0, 1, 0), minirt->camera.look));
				minirt->camera.from = tadd(minirt->camera.from, tmul_scalar(p, 0.5));
			}
			break;

		case D_UP:
			if (minirt->camera.look.y <= 1)
				minirt->camera.look.y += 0.1;
			break;

		case D_DOWN:
			if (minirt->camera.look.y >= -1)
				minirt->camera.look.y -= 0.1;
			break;

		case D_LEFT:
			if (minirt->camera.look.x >= -1)
				minirt->camera.look.x -= 0.1;
			break;

		case D_RIGHT:
			if (minirt->camera.look.x <= 1)
				minirt->camera.look.x += 0.1;
			break;
		default:
			return (0);
	}
	for (size_t y = 0; y < HEIGHT; y++)
		for (size_t x = 0; x < WIDTH; x++)
			mlx_pixel_img_put(minirt, x, y, 0x000000);
	set_camera_view_matrix(minirt, minirt->camera.from, minirt->camera.look);
	render_img(minirt);
	return (0);
}

void	launch_loop(t_minirt *backpack)
{
	mlx_hook(backpack->mlx.win, 17, 0, good_exit, backpack);
	mlx_hook(backpack->mlx.win, 2, (1L<<0), key_press, backpack);
	mlx_loop(backpack->mlx.ptr);
}
