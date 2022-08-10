/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:55:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 22:11:10 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "mlx_utils.h"
#include "libft.h"
#include "minirt_lexer.h"
#include <stdlib.h>
#include <stdio.h>

int	good_exit(t_minirt *backpack)
{
	destruct_mlx(&backpack->mlx);
	ft_lstclear(&backpack->start_lexer, free_token);
	ft_lstclear(&backpack->scene.light, &free);
	ft_lstclear(&backpack->scene.objs, &free);
	exit(0);
	return (0);
}
