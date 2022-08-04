/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:59:46 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/01 17:02:27 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include "end.h"
#include "renderer.h"
#include <pthread.h>
#include <string.h>
#include "matrix.h"
#include "tuple.h"
#include <math.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	t_minirt	minirt;
	memset(&minirt, 0, sizeof(t_minirt));

	(void) ac;
	(void)av;
	/*if (ac != 2)
	{
		ft_putstr_fd(BAD_NB_ARG, 2);
		return (0);
	}*/
	/*t_matrix4 A = {.m = {{8, -5, 9, 2},
		{7, 5, 6, 1},
		{-6, 0, 9, 6},
		{-3, 0, -9, -4}}};
	print_matrix4(A);
	print_matrix4(matrix4_inv(A));*/
	if (!init_mlx_struct(&minirt.mlx))
		return (1);

	t_vec3 forward = vector(0, 0, 1);
	t_vec3 up = vec_norm(vector(0.5, 1, 0));
	t_vec3 right = vec_norm(vec_cross(up, forward));
	t_vec3 true_forward = vec_norm(vec_cross(right, up));

	tprint(right);
	tprint(up);
	tprint(true_forward);
	puts("");

	render_img(&minirt);
	launch_loop(&minirt);
	/*mlx_hook(minirt.mlx.win, 17, 0, good_exit, &minirt.mlx);
	mlx_key_hook(minirt.mlx.win, select_hook, &minirt);
	ft_putstr_fd("OK", 2);
	mlx_loop(minirt.mlx.ptr);*/
	return (0);
}
