/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:29:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 13:35:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREADING_BONUS_H
# define MULTITHREADING_BONUS_H

# include "minirt_struct.h"

void	setup_workers(t_minirt *minirt);
void	*launch_workers(t_minirt *minirt);

#endif
