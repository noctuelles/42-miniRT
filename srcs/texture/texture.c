/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:21:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/09 17:03:18 by plouvel          ###   ########.fr       */
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

	texture.type = TX_CHECKER;
	texture.width = width;
	texture.height = height;
	texture.checker_color[0] = get_norm_color(a);
	texture.checker_color[1] = get_norm_color(b);
	return (texture);
}

t_texture	*create_image_texture(void *mlx, t_texture *texture,
		const char *path)
{
	texture->texel.img = mlx_xpm_file_to_image(mlx, (char *) path,
			&texture->width,
			&texture->height);
	if (texture->texel.img)
	{
		texture->texel.addr = mlx_get_data_addr(texture->texel.img,
				&texture->texel.bits_per_pixel,
				&texture->texel.line_length,
				&texture->texel.endian);
		texture->type = TX_IMAGE;
		return (texture);
	}
	return (NULL);
}

t_texture	*apply_normal_map_to_texture(void *mlx, t_texture *texture,
		const char *path)
{
	if (texture->type == TX_IMAGE)
	{
		texture->nmap.img = mlx_xpm_file_to_image(mlx, (char *) path,
				&texture->nwidth, &texture->nheight);
		if (texture->nwidth != texture->width
			|| texture->nheight != texture->height)
		{
			mlx_destroy_image(mlx, texture->nmap.img);
			texture->nmap.img = NULL;
		}
		if (texture->nmap.img)
		{
			texture->nmap.addr = mlx_get_data_addr(texture->nmap.img,
					&texture->nmap.bits_per_pixel,
					&texture->nmap.line_length,
					&texture->nmap.endian);
			texture->type = TX_IMAGEW_NMAP;
			return (texture);
		}
	}
	return (NULL);
}

void	apply_obj_texture(t_object *obj, t_texture texture)
{
	obj->texture = texture;
}
