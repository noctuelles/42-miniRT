/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:10:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 14:00:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "define.h"

unsigned int	set_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

t_color	get_norm_color(uint32_t color)
{
	t_color	tcolor;

	tcolor.x = (int) (color >> 16) / 255.;
	tcolor.y = (int) (0xFF & color >> 8) / 255.;
	tcolor.z = (int) (0xFF & color) / 255.;
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
