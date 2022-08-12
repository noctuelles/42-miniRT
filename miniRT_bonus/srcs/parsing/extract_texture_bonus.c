/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:43:37 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 21:47:54 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "minirt_lexer_bonus.h"
#include "texture_bonus.h"
#include "scene_bonus.h"
#include "libft.h"
#include "tuple_bonus.h"
#include "parsing_bonus.h"
#include "define_bonus.h"

void	take_texture(t_minirt *minirt, t_list **lexer, t_object *obj)
{
	if (((t_token *)(*lexer)->content)->type != T_VALUE)
		bad_exit_msg(minirt, "invalid texture format.", NULL);
	*lexer = (*lexer)->next;
	if (!create_image_texture(minirt->mlx.ptr, &obj->texture,
			((t_token *)(*lexer)->content)->value))
		bad_exit_msg(minirt, "texture creation failed.",
			((t_token *)(*lexer)->content)->value);
	*lexer = (*lexer)->next;
}

void	take_texture_normal(t_minirt *minirt, t_list **lexer, t_object *obj)
{
	if (((t_token *)(*lexer)->content)->type != T_VALUE
		|| ((t_token *)(*lexer)->next->content)->type != T_VALUE)
		bad_exit_msg(minirt, "invalid texture normal format.", NULL);
	*lexer = (*lexer)->next;
	if (!create_image_texture(minirt->mlx.ptr,
			&obj->texture, ((t_token *)(*lexer)->content)->value))
		bad_exit_msg(minirt, "texture creation failed.",
			((t_token *)(*lexer)->content)->value);
	*lexer = (*lexer)->next;
	if (!apply_normal_map_to_texture(minirt->mlx.ptr,
			&obj->texture, ((t_token *)(*lexer)->content)->value))
		bad_exit_msg(minirt, "texture normal creation failed.",
			((t_token *)(*lexer)->content)->value);
	*lexer = (*lexer)->next;
}

void	take_checker(t_minirt *minirt, t_list **lexer, t_object *obj,
			t_object_type type)
{
	uint32_t	color1;
	uint32_t	color2;

	*lexer = (*lexer)->next;
	if (!extract_color(lexer, &color1))
		bad_exit_msg(minirt, "invalid checker color.", NULL);
	if (!extract_color(lexer, &color2))
		bad_exit_msg(minirt, "invalid checker color.", NULL);
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
	if (((t_token *)(*lexer)->content)->type == T_NEWLINE)
		return (true);
	if (ft_strcmp(((t_token *)(*lexer)->content)->value, "texture") == 0
		&& type != O_PLAN)
		take_texture(minirt, lexer, obj);
	else if (ft_strcmp(((t_token *)(*lexer)->content)->value,
		"texture_normal") == 0 && type != O_PLAN)
		take_texture_normal(minirt, lexer, obj);
	else if (ft_strcmp(((t_token *)(*lexer)->content)->value, "checker") == 0)
		take_checker(minirt, lexer, obj, type);
	return (true);
}
