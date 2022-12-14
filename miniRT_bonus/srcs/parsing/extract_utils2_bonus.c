/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:08:19 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 18:12:11 by bsavinel         ###   ########.fr       */
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

bool	extract_point(t_list **lexer, t_point3 *place)
{
	double	cor[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!(*lexer) || (i != 2 && !((*lexer)->next)))
			return (false);
		if ((((t_token *)(*lexer)->content)->type != T_VALUE
			&& (((t_token *)(*lexer)->next->content)->type != T_COMMA
			|| i == 2))
			|| !ft_isdouble(((t_token *)(*lexer)->content)->value))
			return (false);
		cor[i] = ft_atof(((t_token *)(*lexer)->content)->value);
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

bool	extract_vector_norm(t_list **lexer, t_vec3 *vect)
{
	double	cor[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!(*lexer) || (i != 2 && !((*lexer)->next)))
			return (false);
		if ((((t_token *)(*lexer)->content)->type != T_VALUE
			&& (((t_token *)(*lexer)->next->content)->type != T_COMMA
			|| i == 2))
			|| !ft_isdouble(((t_token *)(*lexer)->content)->value))
			return (false);
		cor[i] = ft_atof(((t_token *)(*lexer)->content)->value);
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
		if ((((t_token *)(*lexer)->content)->type != T_VALUE
			&& (((t_token *)(*lexer)->next->content)->type != T_COMMA
			|| i == 2))
			|| !ft_stronly_digits(((t_token *)(*lexer)->content)->value))
			return (false);
		cor[i] = ft_atoi(((t_token *)(*lexer)->content)->value);
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
