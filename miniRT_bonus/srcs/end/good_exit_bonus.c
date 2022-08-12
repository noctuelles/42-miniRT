/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_exit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:55:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/12 16:05:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "mlx_utils_bonus.h"
#include "mlx.h"
#include "libft.h"
#include "define_bonus.h"
#include "minirt_lexer_bonus.h"
#include <stdlib.h>
#include <stdio.h>

void	free_object(t_minirt *minirt)
{
	t_list	*tmp;

	while (minirt->scene.objs)
	{
		if (((t_object *)minirt->scene.objs->content)->texture.type == TX_IMAGE
			|| ((t_object *)minirt->scene.objs->content)->texture.type
			== TX_IMAGEW_NMAP)
			mlx_destroy_image(minirt->mlx.ptr,
				((t_object *)minirt->scene.objs->content)->texture.texel.img);
		if (((t_object *)minirt->scene.objs->content)->texture.type
			== TX_IMAGEW_NMAP)
			mlx_destroy_image(minirt->mlx.ptr,
				((t_object *)minirt->scene.objs->content)->texture.nmap.img);
		tmp = minirt->scene.objs;
		minirt->scene.objs = minirt->scene.objs->next;
		ft_lstdelone(tmp, &free);
	}
}

void	free_program(t_minirt *minirt)
{
	ft_lstclear(&minirt->start_lexer, free_token);
	ft_lstclear(&minirt->scene.light, &free);
	free_object(minirt);
	destruct_mlx(&minirt->mlx);
}

int	good_exit(t_minirt *minirt)
{
	free_program(minirt);
	exit(0);
	return (0);
}
