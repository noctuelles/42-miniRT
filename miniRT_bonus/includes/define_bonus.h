/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:10:25 by bsavinel          #+#    #+#             */
/*   Updated: 2022/12/14 18:20:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_BONUS_H
# define DEFINE_BONUS_H

# include <stddef.h> // -> NULL

# ifndef D_BONUS
#  define D_BONUS 1
# endif

# define STR_PRG_NAME "miniRT_bonus"
# define STR_BAD_THREAD "minirt: an error occured during thread creation.\n"

/*
 *	Program related define 
 */

# define WIDTH  1280
# define HEIGHT 720
# define THREAD_NBR 8

# define EPSILON 0.0001
# define L_POWER 6.0e1

/*
 *	Define hook
 */

# define D_ESCAPE 65307

/*# define D_W 0x77
# define D_A 0x61
# define D_S 0x73
# define D_D 0x64*/

# define D_Z 0x7A
# define D_Q 0x71
# define D_S 0x73
# define D_D 0x64

# define D_UP 0xff52
# define D_DOWN 0xff54
# define D_LEFT 0xff51
# define D_RIGHT 0xff53

/*
 *	Error message
 */

# define STR_BAD_NB_ARG "Error\nminirt: incorrect number of arguments.\n\
usage: %s <file_name>.rt\n"

#endif
