/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:10:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/11 16:49:24 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "define_bonus.h"

t_color	get_norm_color(uint32_t color)
{
	t_color	tcolor;

	tcolor.x = (int)(color >> 16) / 255.;
	tcolor.y = (int)(0xFF & color >> 8) / 255.;
	tcolor.z = (int)(0xFF & color) / 255.;
	tcolor.w = 0;
	return (tcolor);
}

void	mlx_pixel_img_put(t_minirt *minirt, int x, int y, int color)
{
	char	*dst;

	dst = minirt->mlx.img.addr + y * minirt->mlx.img.line_length
		+ x * (minirt->mlx.img.bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}
