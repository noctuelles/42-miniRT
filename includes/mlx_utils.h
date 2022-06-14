/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:11:59 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/14 14:27:46 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "minirt_struct.h"

/*
 *	mlx_struct_manage.c
 */

int		init_mlx_struct(t_mlx *mlx);
int		destruct_mlx(t_mlx *mlx);

/*
 * launch_loop.c
 */

int		select_hook(int hook, t_minirt *backpack);
void	launch_loop(t_minirt *backpack);

#endif