/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:29:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/11 16:52:02 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREADING_H
# define MULTITHREADING_H

# include "minirt_struct.h"

void	setup_workers(t_minirt *minirt);
void	*launch_workers(t_minirt *minirt);

#endif
