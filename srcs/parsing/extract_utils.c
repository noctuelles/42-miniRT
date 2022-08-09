/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:59 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/09 17:03:53 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "minirt_lexer.h"
#include "scene.h"
#include "libft.h"
#include "tuple.h"
#include "parsing.h"
#include "define.h"

bool	extract_point(t_list **lexer, t_point3 *place)
{
	double cor[3];
	int i;
	
	i = 0;
	while (D_LEX_CONTENT->type != T_NULL && i < 3)
	{
		if (D_LEX_CONTENT->type != T_VALUE && (((t_token *)(*lexer)->next->content)->type != T_COMMA || i == 2))
			return (false);
		cor[i] = ft_atof(D_LEX_CONTENT->value);
		*lexer = (*lexer)->next;
		if (i != 2)
			*lexer = (*lexer)->next;
		i++;
	}
	if (i != 3)
		return false;
	*place = point(cor[0], cor[1], cor[2]);
	return (true);
}

bool	extract_vector(t_list **lexer, t_vec3 *vect)
{
	double cor[3];
	int i;
	
	i = 0;
	while (D_LEX_CONTENT->type != T_NULL && i < 3)
	{
		if (D_LEX_CONTENT->type != T_VALUE && (((t_token *)(*lexer)->next->content)->type != T_COMMA || i == 2))
			return (false);
		cor[i] = ft_atof(D_LEX_CONTENT->value);
		*lexer = (*lexer)->next;
		if (i != 2)
			*lexer = (*lexer)->next;
		i++;
	}
	if (i != 3)
		return false;
	*vect = vector(cor[0], cor[1], cor[2]);
	return (true);
}

bool	extract_vector_norm(t_list **lexer, t_vec3 *vect)
{
	double cor[3];
	int i;
	
	i = 0;
	while (D_LEX_CONTENT->type != T_NULL && i < 3)
	{
		if (D_LEX_CONTENT->type != T_VALUE && (((t_token *)(*lexer)->next->content)->type != T_COMMA || i == 2))
			return (false);
		cor[i] = ft_atof(D_LEX_CONTENT->value);
		if (cor[i] > 1 || cor[i] < -1)
			return false;
		*lexer = (*lexer)->next;
		if (i != 2)
			*lexer = (*lexer)->next;
		i++;
	}
	if (i != 3)
		return false;
	*vect = vector(cor[0], cor[1], cor[2]);
	return (true);
}

bool	extract_color(t_list **lexer, uint32_t *color)
{
	int cor[3];
	int i;
	
	i = 0;
	while (D_LEX_CONTENT->type != T_NULL && i < 3)
	{
		if (D_LEX_CONTENT->type != T_VALUE && (((t_token *)(*lexer)->next->content)->type != T_COMMA || i == 2))
			return (false);
		cor[i] = ft_atoi(D_LEX_CONTENT->value);
		if (cor[i] > 255 || cor[i] < 0)
			return false;
		*lexer = (*lexer)->next;
		if (i != 2)
			*lexer = (*lexer)->next;
		i++;
	}
	if (i != 3)
		return false;
	*color = cor[0] << 16 | cor[1] << 8 | cor[2];
	return (true);
}

bool	extract_double_pos(t_list **lexer, double *dbl)
{
	if (D_LEX_CONTENT->type != T_VALUE)
		return (false);
	*dbl = ft_atof(D_LEX_CONTENT->value);
	*lexer = (*lexer)->next;
	if (*dbl < 0)
		return false;
	return (true);
}

bool	extract_double_range(t_list **lexer, double *dbl, double min, double max)
{
	if (D_LEX_CONTENT->type != T_VALUE)
		return (false);
	*dbl = ft_atof(D_LEX_CONTENT->value);
	*lexer = (*lexer)->next;
	if (*dbl < min || *dbl > max)
		return false;
	return (true);
}