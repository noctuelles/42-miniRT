/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:08:19 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 22:32:05 by bsavinel         ###   ########.fr       */
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

bool	extract_point(t_list **lexer, t_point3 *place)
{
	double	cor[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!(*lexer) || (i != 2 && !((*lexer)->next)))
			return (false);
		if ((D_LEX_CONTENT->type != T_VALUE
			&& (D_LEX_NEXT_CONTENT->type != T_COMMA || i == 2))
			|| !ft_isdouble(D_LEX_CONTENT->value))
			return (false);
		cor[i] = ft_atof(D_LEX_CONTENT->value);
		*lexer = (*lexer)->next;
		if (i != 2)
			*lexer = (*lexer)->next;
		i++;
	}
	if (i != 3)
		return (false);
	*place = point(cor[0], cor[1], cor[2]);
	return (true);
}

bool	extract_vector(t_list **lexer, t_vec3 *vect)
{
	double	cor[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!(*lexer) || (i != 2 && !((*lexer)->next)))
			return (false);
		if ((D_LEX_CONTENT->type != T_VALUE
			&& (D_LEX_NEXT_CONTENT->type != T_COMMA || i == 2))
			|| !ft_isdouble(D_LEX_CONTENT->value))
			return (false);
		cor[i] = ft_atof(D_LEX_CONTENT->value);
		*lexer = (*lexer)->next;
		if (i != 2)
			*lexer = (*lexer)->next;
		i++;
	}
	if (i != 3)
		return (false);
	*vect = vector(cor[0], cor[1], cor[2]);
	return (true);
}

bool	extract_vector_norm(t_list **lexer, t_vec3 *vect)
{
	double	cor[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!(*lexer) || (i != 2 && !((*lexer)->next)))
			return (false);
		if ((D_LEX_CONTENT->type != T_VALUE
			&& (D_LEX_NEXT_CONTENT->type != T_COMMA || i == 2))
			|| !ft_isdouble(D_LEX_CONTENT->value))
			return (false);
		cor[i] = ft_atof(D_LEX_CONTENT->value);
		if (cor[i] > 1 || cor[i] < -1)
			return (false);
		*lexer = (*lexer)->next;
		if (i != 2)
			*lexer = (*lexer)->next;
		i++;
	}
	if (i != 3)
		return (false);
	*vect = vector(cor[0], cor[1], cor[2]);
	return (true);
}

bool	extract_color(t_list **lexer, uint32_t *color)
{
	int	cor[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(*lexer) || (i != 2 && !((*lexer)->next)))
			return (false);
		if ((D_LEX_CONTENT->type != T_VALUE
			&& (D_LEX_NEXT_CONTENT->type != T_COMMA || i == 2))
			|| !ft_stronly_digits(D_LEX_CONTENT->value))
			return (false);
		cor[i] = ft_atoi(D_LEX_CONTENT->value);
		if (cor[i] > 255 || cor[i] < 0)
			return (false);
		*lexer = (*lexer)->next;
		if (i != 2)
			*lexer = (*lexer)->next;
		i++;
	}
	if (i != 3)
		return (false);
	*color = cor[0] << 16 | cor[1] << 8 | cor[2];
	return (true);
}
