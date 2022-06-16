/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:59:46 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/15 23:28:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include "end.h"
#include "renderer.h"
#include <pthread.h>
#include <string.h>

int	main(int ac, char **av)
{
	t_minirt	minirt;
	memset(&minirt, 0, sizeof(t_minirt));

	(void) ac;
	(void)av;
	/*if (ac != 2)
	{
		ft_putstr_fd(BAD_NB_ARG, 2);
		return (0);
	}*/
	if (!init_mlx_struct(&minirt.mlx))
		return (1);
	render_img(&minirt);
	launch_loop(&minirt);
	/*mlx_hook(minirt.mlx.win, 17, 0, good_exit, &minirt.mlx);
	mlx_key_hook(minirt.mlx.win, select_hook, &minirt);
	ft_putstr_fd("OK", 2);
	mlx_loop(minirt.mlx.ptr);*/
	return (0);
}
