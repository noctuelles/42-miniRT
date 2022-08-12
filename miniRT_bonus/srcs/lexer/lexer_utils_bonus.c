/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:56:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 15:44:32 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt_lexer_bonus.h"
#include <stdlib.h>

t_token	search_known_token(const char *str)
{
	if (ft_strncmp(str, STR_SPHERE, 2) == 0)
		return (set_token(STR_SPHERE, T_SPHERE));
	if (ft_strncmp(str, STR_PLAN, 2) == 0)
		return (set_token(STR_PLAN, T_PLAN));
	if (ft_strncmp(str, STR_CYLINDER, 2) == 0)
		return (set_token(STR_CYLINDER, T_CYLINDER));
	if (ft_strncmp(str, STR_CONE, 2) == 0)
		return (set_token(STR_CONE, T_CONE));
	if (ft_strncmp(str, STR_AMBIANT_LIGHT, 1) == 0)
		return (set_token(STR_AMBIANT_LIGHT, T_AMBIANT_LIGHT));
	if (ft_strncmp(str, STR_CAMERA, 1) == 0)
		return (set_token(STR_CAMERA, T_CAMERA));
	if (ft_strncmp(str, STR_LIGHT, 1) == 0)
		return (set_token(STR_LIGHT, T_LIGHT));
	if (ft_strncmp(str, STR_COMMA, 1) == 0)
		return (set_token(STR_COMMA, T_COMMA));
	if (ft_strncmp(str, STR_NEWLINE, 1) == 0)
		return (set_token(STR_NEWLINE, T_NEWLINE));
	if (ft_strncmp(str, STR_SPACE, 1) == 0)
		return (set_token(STR_SPACE, T_BREAK));
	if (ft_strncmp(str, STR_TAB, 1) == 0)
		return (set_token(STR_TAB, T_BREAK));
	return (set_token(NULL, T_NULL));
}

void	*add_known_token_to_list(t_lexer *lexer)
{
	lexer->line += lexer->tkn.len;
	if (lexer->tkn.type != T_BREAK)
	{
		if (lexer->tkn.type == T_AMBIANT_LIGHT)
			lexer->declared_ambiant_light++;
		if (lexer->tkn.type == T_CAMERA)
			lexer->declared_camera++;
		if (lexer->tkn.type == T_LIGHT)
			lexer->declared_light++;
	}
	if (add_token_to_list(lexer, lexer->tkn.value, lexer->tkn.len,
			lexer->tkn.type) == NULL)
		return (NULL);
	lexer->prev = lexer->line;
	return (lexer);
}

t_token	*add_token_to_list(t_lexer *lexer, char *value, size_t len,
		t_token_type type)
{
	char	*str;
	t_list	*elem;
	t_token	*tkn;

	str = value;
	if (type == T_VALUE)
	{
		str = ft_strndup(value, len);
		if (!str)
			return (NULL);
	}
	tkn = new_token(str, len, type);
	if (tkn)
	{
		elem = ft_lstnew(tkn);
		if (elem)
		{
			ft_lstadd_back(&lexer->list_tkns, elem);
			return (tkn);
		}
		free_token(tkn);
	}
	else if (type == T_VALUE)
		free(str);
	return (NULL);
}

bool	analysis_syntax(t_list	*tkns)
{
	t_list	*elem;
	t_token	*tkn;
	t_token	*prev_tkn;

	elem = tkns;
	prev_tkn = NULL;
	while (elem)
	{
		tkn = elem->content;
		if (prev_tkn)
		{
			if ((prev_tkn->type == T_VALUE) && (tkn->type != T_NEWLINE
					&& tkn->type != T_COMMA && tkn->type != T_BREAK
					&& tkn->type != T_NULL))
				return (false);
			else if ((prev_tkn->type >= T_AMBIANT_LIGHT && prev_tkn->type
					<= T_PLAN) && tkn->type != T_BREAK)
				return (false);
		}
		prev_tkn = tkn;
		elem = elem->next;
	}
	return (true);
}

void	remove_break_tokens(t_list **tkns)
{
	t_list	*elem;
	t_list	*prev_elem;
	t_token	*tkn;

	elem = *tkns;
	prev_elem = NULL;
	while (elem)
	{
		tkn = elem->content;
		if (prev_elem && tkn->type == T_BREAK)
		{
			prev_elem->next = elem->next;
			ft_lstdelone(elem, free);
			elem = prev_elem;
		}
		prev_elem = elem;
		elem = elem->next;
	}
	if (((t_token *)(*tkns)->content)->type == T_BREAK)
	{
		elem = (*tkns)->next;
		ft_lstdelone(*tkns, free);
		*tkns = elem;
	}
}
