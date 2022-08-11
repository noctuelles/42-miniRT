/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:11:59 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 17:46:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "minirt_struct.h"

/*
 *	mlx_struct_manage.c
 */

bool	init_mlx_window(t_minirt *minirt);
int		init_mlx_struct(t_mlx *mlx);
int		destruct_mlx(t_mlx *mlx);

/*
 * launch_loop.c
 */

void	launch_loop(t_minirt *backpack);

/*
 *	mlx_utils.c
 */

t_color	get_norm_color(uint32_t color);
void	mlx_pixel_img_put(t_minirt *minirt, int x, int y, int color);

#endif
