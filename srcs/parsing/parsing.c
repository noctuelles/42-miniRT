/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:43:46 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/09 16:43:10 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "minirt_lexer.h"
#include "scene.h"
#include "libft.h"
#include "tuple.h"
#include "parsing.h"
#include "define.h"

bool	skip_break(t_list **lexer)
{
	bool retour;
	
	retour = false;
	while (D_LEX_CONTENT->type == T_BREAK)
	{
		*lexer = (*lexer)->next;
		retour = true;
	}
	return (retour)
}

bool feed_scene(t_minirt *minirt, t_list **lexer)
{
	bool	new_line;
	int		line;

	line = 1;
	while (D_LEX_CONTENT->type = T_NULL)
	{
		new_line = false;
		if (D_LEX_CONTENT->type == T_SPHERE)
			extract_sphere(minirt, lexer, line);
		else if (D_LEX_CONTENT->type == T_PLAN)
			extract_plan(minirt, lexer, line);
		else if (D_LEX_CONTENT->type == T_CYLINDER)
			extract_cylinder(minirt, lexer, line);
		else if (D_LEX_CONTENT->type = T_CAMERA)
			extract_camera(minirt, lexer, line);
		else if (D_LEX_CONTENT->type = T_LIGHT)
			extract_light(minirt, lexer, line);
		else if (D_LEX_CONTENT->type = T_AMBIANT_LIGHT)
			extract_ambiante_light(minirt, lexer, line);
		while (D_LEX_CONTENT->type == T_NEWLINE || D_LEX_CONTENT->type == T_BREAK)
		{
			if (D_LEX_CONTENT->type == T_NEWLINE)
			{
				line++;
				new_line = true;
			}
			*lexer = (*lexer)->next;
		}
		if (new_line == false && lexer) //! reste information qui ne peuvent etre traite
			bad_exit_msg(minirt, lexer, "Bad format line: ", line);
	}
	return (true);
}

bool	parser(t_minirt *minirt, char *filename)
{
	t_list	*lex_file;

	lex_file = lex_from_file(filename);
	if (lex_file == NULL)
	{
		printf("exit apres lexing\n");
		exit(0);
	}
	if (!feed_scene(minirt, &lex_file))
	{
		exit(0);
	}
}