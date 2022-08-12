/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:20:30 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/12 16:05:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef END_BONUS_H
# define END_BONUS_H

# include "minirt_struct_bonus.h"

/*
 *	good_exit.c
 */

void	free_object(t_minirt *minirt);
void	free_program(t_minirt *minirt);
int		good_exit(t_minirt *minirt);

#endif
