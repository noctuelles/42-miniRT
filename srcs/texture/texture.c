/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:21:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/26 00:30:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "mlx_utils.h"
#include <math.h>
#include "mlx.h"

t_texture	create_checkered_texture(int width, int height, uint32_t a,
		uint32_t b)
{
	t_texture	texture;

	texture.texture_type = TX_CHECKER;
	texture.width = width;
	texture.height = height;
	texture.checker_color[0] = get_norm_color(a);
	texture.checker_color[1] = get_norm_color(b);
	return (texture);
}

t_texture	create_image_texture(void *mlx, const char *path)
{
	t_texture	texture;
	texture.texture_type = TX_IMAGE;
	texture.img.img = mlx_xpm_file_to_image(mlx, (char *) path, &texture.width,
			&texture.height);
	if (texture.img.img)
	{
		texture.img.addr = mlx_get_data_addr(texture.img.img,
				&texture.img.bits_per_pixel,
				&texture.img.line_length,
				&texture.img.endian);
	}
	else
		texture.texture_type = TX_FAILED;
	return (texture);
}

t_color	get_image_color(t_texture texture, t_uv uv)
{
	uint32_t	color;
	char		*dest;
	size_t		x;
	size_t		y;

	x = roundf(uv.u * texture.width);
	y = roundf(uv.v * texture.height);
	dest = texture.img.addr + x * (texture.img.bits_per_pixel / 8) +
		(texture.height - y) * texture.img.line_length;
	color = * (uint32_t *) dest;
	return (get_norm_color(color));
}

t_color	get_checker_color(t_texture texture, t_uv uv)
{
	size_t	x;
	size_t	y;

	x = roundf(uv.u * texture.width);
	y = roundf(uv.v * texture.height);
	if ((x + y) % 2 == 0)
		return (texture.checker_color[0]);
	else
		return (texture.checker_color[1]);
}

void	apply_obj_texture(t_object *obj, t_texture texture)
{
	obj->texture = texture;
}
