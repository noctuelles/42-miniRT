/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:54:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 15:45:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_lexer_bonus.h"
#include "libft.h"
#include <stdlib.h>

static void	*quit(t_lexer *lexer, t_lexer_errcode errcode)
{
	ft_lstclear(&lexer->list_tkns, free_token);
	if (errcode == E_LEX_TOO_MUCH_AMLIGHT)
		print_error_line_nbr(STR_TOO_MUCH_AMLIGHT, lexer->line_nbr);
	else if (errcode == E_LEX_TOO_MUCH_CAMERA)
		print_error_line_nbr(STR_TOO_MUCH_CAMERA, lexer->line_nbr);
	else if (errcode == E_LEX_MALLOC)
		print_error_function(STR_FUNCTION_MALLOC);
	lexer->errcode = errcode;
	return (NULL);
}

static void	*finish_line(t_lexer *lexer)
{
	if (lexer->declared_ambiant_light > 1)
		return (quit(lexer, E_LEX_TOO_MUCH_AMLIGHT));
	else if (lexer->declared_camera > 1)
		return (quit(lexer, E_LEX_TOO_MUCH_CAMERA));
	if (lexer->prev != lexer->line)
	{
		if (add_token_to_list(lexer, (char *) lexer->prev,
				lexer->line - lexer->prev, T_VALUE) == NULL)
			return (quit(lexer, E_LEX_MALLOC));
	}
	lexer->line_nbr++;
	lexer->line = lexer->file_content[lexer->line_nbr];
	return (lexer);
}

static void	*finish_lexing(t_lexer *lexer)
{
	if (add_token_to_list(lexer, NULL, 0, T_NULL) == NULL)
		return (quit(lexer, E_LEX_MALLOC));
	return (lexer->list_tkns);
}

static t_list	*lex_file(t_lexer *lexer)
{
	while (lexer->file_content[lexer->line_nbr] != NULL)
	{
		lexer->prev = lexer->line;
		while (*lexer->line != '\0')
		{
			lexer->tkn = search_known_token(lexer->line);
			if (lexer->tkn.type != T_NULL)
			{
				if (lexer->line != lexer->prev)
				{
					if (add_token_to_list(lexer, (char *) lexer->prev,
							lexer->line - lexer->prev, T_VALUE) == NULL)
						return (quit(lexer, E_LEX_MALLOC));
				}
				if (add_known_token_to_list(lexer) == NULL)
					return (quit(lexer, E_LEX_MALLOC));
			}
			else
				lexer->line++;
		}
		if (!finish_line(lexer))
			return (NULL);
	}
	return (finish_lexing(lexer));
}

t_list	*lex_from_file(const char *filename)
{
	t_lexer	lexer;
	ssize_t	i;

	ft_memset(&lexer, 0, sizeof(lexer));
	lexer.file_content = read_file(filename);
	if (lexer.file_content)
	{
		i = 0;
		lexer.line = *lexer.file_content;
		lexer.list_tkns = lex_file(&lexer);
		while (lexer.file_content[i] != NULL)
			free(lexer.file_content[i++]);
		if (lexer.list_tkns)
		{
			if (!check_valid_lexing(&lexer))
				ft_lstclear(&lexer.list_tkns, free_token);
			else
				remove_break_tokens(&lexer.list_tkns);
		}
	}
	free(lexer.file_content);
	return (lexer.list_tkns);
}
