/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:52:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/11 14:53:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_lexer.h"

bool	check_valid_lexing(t_lexer *lexer)
{
	bool	validity;

	if (!analysis_syntax(lexer->list_tkns))
	{
		print_error(STR_INVALID_SYNTAX);
		validity = false;
	}
	else if (lexer->declared_camera == 0)
	{
		print_error(STR_NO_CAMERA);
		validity = false;
	}
	else
		validity = true;
	if (validity && lexer->declared_ambiant_light == 0)
		print_warning(STR_NO_AMBIANT_LIGHT);
	return (validity);
}
