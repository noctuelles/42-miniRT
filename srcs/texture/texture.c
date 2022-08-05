/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:21:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/05 16:58:59 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "mlx_utils.h"
#include "math.h"
#include <math.h>
#include "tuple.h"
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

bool	apply_normal_map_to_texture(void *mlx, t_texture *texture,
		const char *path)
{
	if (texture->texture_type == TX_IMAGE)
	{
		texture->nmap.img = mlx_xpm_file_to_image(mlx, (char *) path,
				&texture->width, &texture->height);
		if (texture->nmap.img)
		{
			texture->nmap.addr = mlx_get_data_addr(texture->nmap.img,
					&texture->nmap.bits_per_pixel,
					&texture->nmap.line_length,
					&texture->nmap.endian);
			texture->texture_type = TX_IMAGEW_NMAP;
		}
		else
			return (false);
		return (true);
	}
	return (false);
}

t_color	get_image_color(t_texture texture, t_uv uv)
{
	uint32_t	color;
	char		*dest;
	size_t		x;
	size_t		y;

	x = floor(uv.u * (texture.width - 1));
	y = floor(uv.v * (texture.height - 1));
	dest = texture.img.addr + x * (texture.img.bits_per_pixel / 8) +
		(texture.height - y) * texture.img.line_length;
	color = * (uint32_t *) dest;
	return (get_norm_color(color));
}

t_vec3	get_image_normal(t_texture texture, t_uv uv)
{
	t_vec3		normal;
	uint32_t	color;
	char		*dest;
	size_t		x;
	size_t		y;

	x = floor(uv.u * (texture.width - 1));
	y = floor(uv.v * (texture.height - 1));
	dest = texture.nmap.addr + x * (texture.nmap.bits_per_pixel / 8) +
		(texture.height - y) * texture.nmap.line_length;
	color = * (uint32_t *) dest;
	normal = get_norm_color(color);
	normal.x = normal.x * 2 - 1;
	normal.y = normal.y * 2 - 1;
	normal.z = normal.z * 2 - 1;
	return (vec_norm(normal));
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
