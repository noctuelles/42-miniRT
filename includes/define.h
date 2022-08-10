/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:10:25 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 22:35:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stddef.h> // -> NULL

# define THREAD_NBR 8
#define L_POWER 6.0e1

#define D_LEX_CONTENT ((t_token *)(*lexer)->content)
#define D_LEX_NEXT_CONTENT ((t_token *)(*lexer)->next->content)

#ifndef D_BONUS
# define D_BONUS 1
#endif

/*
 *	Define windows
 */

# define WIDTH  1440 
# define HEIGHT 900

# define EPSILON 0.0001

/*
 *	Temporary define
 */

# define FOV_ANGLE 100.0
# define FOV       (FOV_ANGLE * M_PI) / 180

# define ANGLE(x) (x * M_PI) / 180
/*
 *	Macros
 */

# define DG_RAD(a) ((a * M_PI) / 180)

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
