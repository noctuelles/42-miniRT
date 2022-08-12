/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:23:26 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/08 17:35:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_lexer.h"
#include <stdlib.h>

t_token	set_token(char *str, t_token_type type)
{
	t_token	tkn;

	tkn.value = str;
	tkn.type = type;
	if (str)
		tkn.len = ft_strlen(str);
	return (tkn);
}

t_token	*new_token(char *str, size_t len, t_token_type type)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (NULL);
	tkn->value = str;
	tkn->len = len;
	tkn->type = type;
	return (tkn);
}

void	free_token(void *token)
{
	t_token	*tkn;

	tkn = token;
	if (tkn->type == T_VALUE)
		free(tkn->value);
	free(tkn);
}
