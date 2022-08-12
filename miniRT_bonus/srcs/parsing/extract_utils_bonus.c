/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:59 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 21:43:31 by bsavinel         ###   ########.fr       */
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

bool	extract_double_pos(t_list **lexer, double *dbl)
{
	if (!(*lexer) || ((t_token *)(*lexer)->content)->type != T_VALUE
		|| !ft_isdouble(((t_token *)(*lexer)->content)->value))
		return (false);
	*dbl = ft_atof(((t_token *)(*lexer)->content)->value);
	*lexer = (*lexer)->next;
	if (*dbl <= 0)
		return (false);
	return (true);
}

bool	extract_double_range(t_list **lexer, double *dbl, double min,
								double max)
{
	if (!(*lexer) || ((t_token *)(*lexer)->content)->type != T_VALUE
		|| !ft_isdouble(((t_token *)(*lexer)->content)->value))
		return (false);
	*dbl = ft_atof(((t_token *)(*lexer)->content)->value);
	*lexer = (*lexer)->next;
	if (*dbl < min || *dbl > max)
		return (false);
	return (true);
}
