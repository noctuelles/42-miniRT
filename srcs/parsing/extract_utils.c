/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:04:59 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 13:51:04 by bsavinel         ###   ########.fr       */
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
