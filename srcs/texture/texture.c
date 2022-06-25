/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:21:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 23:47:53 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "mlx_utils.h"
#include <math.h>

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
