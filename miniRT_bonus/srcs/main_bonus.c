/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:59:46 by bsavinel          #+#    #+#             */
/*   Updated: 2022/12/13 15:16:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils_bonus.h"
#include "parsing_bonus.h"
#include "renderer_bonus.h"
#include "multithreading_bonus.h"
#include "ft_dprintf.h"
#include "minirt_lexer_bonus.h"
#include "mlx.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	t_minirt	minirt;

	ft_memset(&minirt, 0, sizeof(t_minirt));
	if (ac != 2)
	{
		if (*av)
			ft_dprintf(STDERR_FILENO, STR_BAD_NB_ARG, *av);
		else
			ft_dprintf(STDERR_FILENO, STR_BAD_NB_ARG, STR_PRG_NAME);
		return (1);
	}
	if (!init_mlx_struct(&minirt.mlx))
		return (1);
	printf("minirt: loading file '%s'...\n", av[1]);
	parser(&minirt, av[1]);
	printf("minirt: successfully loaded.\n");
	if (!init_mlx_window(&minirt))
		return (1);
	setup_workers(&minirt);
	if (!render_img(&minirt))
		return (1);
	launch_loop(&minirt);
	return (0);
}
