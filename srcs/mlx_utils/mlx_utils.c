/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:10:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/15 14:41:09 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "define.h"

unsigned int	set_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	mlx_pixel_img_put(t_minirt *minirt, int x, int y, int color)
{
	char	*dst;

	dst = minirt->mlx.img.addr + ((HEIGHT - y) * minirt->mlx.img.line_length
			+ x * (minirt->mlx.img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
