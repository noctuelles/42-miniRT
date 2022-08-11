/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:20:30 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 16:58:21 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef END_H
# define END_H

#include "minirt_struct.h"

/*
 *	good_exit.c
 */

void	free_object(t_minirt *minirt);
int		good_exit(t_minirt *backpack);

#endif
