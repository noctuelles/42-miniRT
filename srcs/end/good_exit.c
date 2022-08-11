/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:55:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 16:54:34 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "mlx_utils.h"
#include "mlx.h"
#include "libft.h"
#include "define.h"
#include "minirt_lexer.h"
#include <stdlib.h>
#include <stdio.h>

void	free_object(t_minirt *minirt)
{
	t_list	*tmp;

	while (minirt->scene.objs)
	{
		if (D_OBJ_SC_CONTENT->texture.type == TX_IMAGE
			|| D_OBJ_SC_CONTENT->texture.type == TX_IMAGEW_NMAP)
			mlx_destroy_image(minirt->mlx.ptr,
				D_OBJ_SC_CONTENT->texture.texel.img);
		if (D_OBJ_SC_CONTENT->texture.type == TX_IMAGEW_NMAP)
			mlx_destroy_image(minirt->mlx.ptr,
				D_OBJ_SC_CONTENT->texture.nmap.img);
		tmp = minirt->scene.objs;
		minirt->scene.objs = minirt->scene.objs->next;
		ft_lstdelone(tmp, &free);
	}
}

int	good_exit(t_minirt *minirt)
{
	ft_lstclear(&minirt->start_lexer, free_token);
	ft_lstclear(&minirt->scene.light, &free);
	free_object(minirt);
	destruct_mlx(&minirt->mlx);
	exit(0);
	return (0);
}
