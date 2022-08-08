/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:10:25 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/08 15:48:32 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stddef.h> // -> NULL

# define THREAD_NBR 8

/*
 *	Define windows
 */

# define WIDTH  1920 
# define HEIGHT 1200

# define EPSILON 0.00001

/*
 *	Temporary define
 */

# define FOV_ANGLE 90.0
# define FOV       (FOV_ANGLE * M_PI) / 180

# define ANGLE(x) (x * M_PI) / 180
/*
 *	Define hook
 */

# define D_ESCAPE 65307

# define D_W 0x77
# define D_A 0x61
# define D_S 0x73
# define D_D 0x64

/*
 *	Error message
 */

# define BAD_NB_ARG "Bad number of argument\nUse like this ./miniRT <file>\n"

#endif
