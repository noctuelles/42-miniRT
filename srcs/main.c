/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:59:46 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 15:21:27 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include "define.h"
#include "parsing.h"
#include "end.h"
#include "renderer.h"
#include "multithreading.h"
#include "minirt_lexer.h"
#include "minirt_lexer.h"
#include <pthread.h>
#include <string.h>
#include "matrix.h"
#include "texture.h"
#include "scene.h"
#include "tuple.h"
#include "scene.h"
#include <math.h>
#include <stdio.h>
char *translate(t_token_type type)
{
	if (type == 0)
		return ("T_AMBIANT_LIGHT");
	if (type == 1)
		return ("T_CAMERA");
	if (type == 2)
		return ("T_LIGHT");
	if (type == 3)
		return ("T_SPHERE");
	if (type == 4)
		return ("T_PLAN");
	if (type == 5)
		return ("T_CYLINDER");
	if (type == 6)
		return ("T_VALUE");
	if (type == 7)
		return ("T_NEWLINE");
	if (type == 8)
		return ("T_COMMA");
	if (type == 9)
		return ("T_CONE");
	return ("NULL");
}
void	print_tokens(t_list *tkns)
{
	for (t_list *elem = tkns; elem; elem = elem->next)
	{
		t_token *tkn = elem->content;
		printf("<%s> ", translate(tkn->type));
		if (tkn->type == T_NEWLINE)
			printf("\n");
	}
}
int	main(int ac, char **av)
{
	t_minirt	minirt;

	memset(&minirt, 0, sizeof(t_minirt));
	if (ac != 2)
	{
		printf("Error\nBad numeber of argument\n");
		return (1);
	}
	if (!init_mlx_struct(&minirt.mlx))
		return (1);
	parser(&minirt, av[1]);
	setup_workers(&minirt);
	render_img(&minirt);
	launch_loop(&minirt);
	return (0);
}
