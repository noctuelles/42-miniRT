/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:59 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 22:29:04 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "minirt_lexer.h"
#include "texture.h"
#include "scene.h"
#include "libft.h"
#include "tuple.h"
#include "parsing.h"
#include "define.h"

bool	extract_double_pos(t_list **lexer, double *dbl)
{
	if (!(*lexer) || D_LEX_CONTENT->type != T_VALUE
		|| !ft_isdouble(D_LEX_CONTENT->value))
		return (false);
	*dbl = ft_atof(D_LEX_CONTENT->value);
	*lexer = (*lexer)->next;
	if (*dbl < 0)
		return (false);
	return (true);
}

bool	extract_double_range(t_list **lexer, double *dbl, double min,
								double max)
{
	if (!(*lexer) || D_LEX_CONTENT->type != T_VALUE
		|| !ft_isdouble(D_LEX_CONTENT->value))
		return (false);
	*dbl = ft_atof(D_LEX_CONTENT->value);
	*lexer = (*lexer)->next;
	if (*dbl < min || *dbl > max)
		return (false);
	return (true);
}

bool	extract_texture(t_minirt *minirt, t_list **lexer, t_object *obj, double width, double height)
{
	uint32_t	color1;
	uint32_t	color2;

	if (D_LEX_CONTENT->type == T_NEWLINE)
		return (true);
	if (ft_strcmp(D_LEX_CONTENT->value, "texture") == 0)
	{
		if (D_LEX_CONTENT->type != T_VALUE)
			bad_exit_msg(minirt, "Bad format for texture");
		*lexer = (*lexer)->next;
		if (!create_image_texture(minirt->mlx.ptr, &obj->texture, D_LEX_CONTENT->value))
			bad_exit_msg(minirt, "Texture failed");
		*lexer = (*lexer)->next;
	}
	else if (ft_strcmp(D_LEX_CONTENT->value, "texture_normal") == 0)
	{
		if (D_LEX_CONTENT->type != T_VALUE || D_LEX_NEXT_CONTENT->type != T_VALUE)
			bad_exit_msg(minirt, "Bad format for texture");
		*lexer = (*lexer)->next;
		if (!create_image_texture(minirt->mlx.ptr, &obj->texture, D_LEX_CONTENT->value))
			bad_exit_msg(minirt, "Texture failed");
		*lexer = (*lexer)->next;
		if (!apply_normal_map_to_texture(minirt->mlx.ptr, &obj->texture, D_LEX_CONTENT->value))
			bad_exit_msg(minirt, "Texture failed");
		*lexer = (*lexer)->next;
	}
	else if (ft_strcmp(D_LEX_CONTENT->value, "checker") == 0)
	{
		*lexer = (*lexer)->next;
		if (!extract_color(lexer, &color1))
			bad_exit_msg(minirt, "Bad format for checker texture");
		if (!extract_color(lexer, &color2))
			bad_exit_msg(minirt, "Bad format for checker texture");
		obj->texture = create_checkered_texture(width, height, color1, color2);
	}
	return (true);
}
