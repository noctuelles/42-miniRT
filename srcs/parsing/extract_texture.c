/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:43:37 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 14:33:09 by bsavinel         ###   ########.fr       */
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

void	take_texture(t_minirt *minirt, t_list **lexer, t_object *obj)
{
	if (D_LEX_CONTENT->type != T_VALUE)
		bad_exit_msg(minirt, "Bad format for texture");
	*lexer = (*lexer)->next;
	if (!create_image_texture(minirt->mlx.ptr, &obj->texture,
			D_LEX_CONTENT->value))
		bad_exit_msg(minirt, "Texture failed");
	*lexer = (*lexer)->next;
}

void	take_texture_normal(t_minirt *minirt, t_list **lexer, t_object *obj)
{
	if (D_LEX_CONTENT->type != T_VALUE
		|| D_LEX_NEXT_CONTENT->type != T_VALUE)
		bad_exit_msg(minirt, "Bad format for texture normal");
	*lexer = (*lexer)->next;
	if (!create_image_texture(minirt->mlx.ptr,
			&obj->texture, D_LEX_CONTENT->value))
		bad_exit_msg(minirt, "Texture normal failed");
	*lexer = (*lexer)->next;
	if (!apply_normal_map_to_texture(minirt->mlx.ptr,
			&obj->texture, D_LEX_CONTENT->value))
		bad_exit_msg(minirt, "Texture normal failed");
	*lexer = (*lexer)->next;
}

void	take_checker(t_minirt *minirt, t_list **lexer, t_object *obj,
			t_object_type type)
{
	uint32_t	color1;
	uint32_t	color2;

	*lexer = (*lexer)->next;
	if (!extract_color(lexer, &color1))
		bad_exit_msg(minirt, "Bad format for checker texture");
	if (!extract_color(lexer, &color2))
		bad_exit_msg(minirt, "Bad format for checker texture");
	if (type == O_SPHERE)
		obj->texture = create_checkered_texture(8, 8, color1, color2);
	else if (type == O_PLAN)
		obj->texture = create_checkered_texture(4, 4, color1, color2);
	else if (type == O_CYLINDER)
		obj->texture = create_checkered_texture(16, 8, color1, color2);
	else if (type == O_CONE)
		obj->texture = create_checkered_texture(16, 8, color1, color2);
}

bool	extract_texture(t_minirt *minirt, t_list **lexer, t_object *obj,
			t_object_type type)
{
	if (D_LEX_CONTENT->type == T_NEWLINE)
		return (true);
	if (ft_strcmp(D_LEX_CONTENT->value, "texture") == 0)
		take_texture(minirt, lexer, obj);
	else if (ft_strcmp(D_LEX_CONTENT->value, "texture_normal") == 0)
		take_texture_normal(minirt, lexer, obj);
	else if (ft_strcmp(D_LEX_CONTENT->value, "checker") == 0)
		take_checker(minirt, lexer, obj, type);
	return (true);
}
