/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:02:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 13:52:38 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "mlx_utils_bonus.h"
#include "math.h"
#include <math.h>
#include "tuple_bonus.h"
#include "mlx.h"

t_color	get_image_color(t_texture texture, t_uv uv)
{
	uint32_t	color;
	char		*dest;
	size_t		x;
	size_t		y;

	x = floor(uv.u * (texture.width - 1));
	y = floor(uv.v * (texture.height - 1));
	dest = texture.texel.addr + x * (texture.texel.bits_per_pixel / 8)
		+ (texture.height - y) * texture.texel.line_length;
	color = *(uint32_t *) dest;
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
	dest = texture.nmap.addr + x * (texture.nmap.bits_per_pixel / 8)
		+ (texture.height - y) * texture.nmap.line_length;
	color = *(uint32_t *) dest;
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
