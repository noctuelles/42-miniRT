/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:10:25 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/24 18:44:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stddef.h> // -> NULL

/*
 *	Define windows
 */

# define HEIGHT 600
# define WIDTH 600

/*
 *	Temporary define
 */

# define FOV_ANGLE 70.0
# define FOV       (FOV_ANGLE * M_PI) / 180

/*
 *	Define hook
 */

# define D_ESCAPE 65307

/*
 *	Error message
 */

# define BAD_NB_ARG "Bad number of argument\nUse like this ./miniRT <file>\n"

#endif
