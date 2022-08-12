/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:57:05 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 16:05:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define_bonus.h"
#include "minirt_struct_bonus.h"
#include "scene_bonus.h"
#include "mlx_utils_bonus.h"
#include "math_utils_bonus.h"
#include "tuple_bonus.h"
#include "renderer_bonus.h"
#include <stdio.h>
#include "matrix_bonus.h"
#include <math.h>

/* setup_workers() setup each worker's job.
 * The last one has a couple of more rows to do, depending on how big the
 * window screen is and how much threads are dedicated. */

void	setup_workers(t_minirt *minirt)
{
	size_t			i;
	unsigned int	rows_per_worker;

	i = 0;
	rows_per_worker = HEIGHT / THREAD_NBR;
	while (i < THREAD_NBR)
	{
		minirt->workers[i].id = i;
		minirt->workers[i].minirt = minirt;
		minirt->workers[i].assigned_start = i * rows_per_worker;
		minirt->workers[i].assigned_end = minirt->workers[i].assigned_start
			+ rows_per_worker - 1;
		i++;
	}
	minirt->workers[THREAD_NBR - 1].assigned_end += HEIGHT % THREAD_NBR;
}

void	*launch_workers(t_minirt *minirt)
{
	size_t	i;

	i = 0;
	while (i < THREAD_NBR)
	{
		if (pthread_create(&minirt->workers[i].pthread, NULL, &render,
				&minirt->workers[i]) != 0)
			return (NULL);
		i++;
	}
	i = 0;
	while (i < THREAD_NBR)
		pthread_join(minirt->workers[i++].pthread, NULL);
	return (minirt);
}
