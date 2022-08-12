/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_struct_manage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:29:36 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 17:01:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "define_bonus.h"
#include "end_bonus.h"
#include "ft_dprintf.h"
#include "minirt_struct_bonus.h"
#include "minirt_lexer_bonus.h"
#include <stdlib.h>
#include "mlx_utils_bonus.h"

int	init_mlx_struct(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->img.img = NULL;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
	{
		print_error("cannot create mlx instance");
		return (0);
	}
	mlx->img.img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->img.img)
	{
		print_error("cannot create mlx window image");
		return (destruct_mlx(mlx));
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	return (1);
}

bool	init_mlx_window(t_minirt *minirt)
{
	minirt->mlx.win = mlx_new_window(minirt->mlx.ptr, WIDTH, HEIGHT, "miniRT");
	if (!minirt->mlx.win)
	{
		ft_lstclear(&minirt->start_lexer, free_token);
		ft_lstclear(&minirt->scene.light, &free);
		free_object(minirt);
		destruct_mlx(&minirt->mlx);
		print_error("cannot create mlx window");
		return (false);
	}
	return (true);
}

int	destruct_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->img.img)
		mlx_destroy_image(mlx->ptr, mlx->img.img);
	if (mlx->ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
	return (0);
}
