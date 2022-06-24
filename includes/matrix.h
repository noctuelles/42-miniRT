/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:44:54 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/24 18:22:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

#include "minirt_struct.h"

/* matrix.c */

t_matrix4	matrix4_mul(t_matrix4 const A, t_matrix4 const B);
t_tuple		matrix4_tmul(t_matrix4 const A, t_tuple B);
t_matrix4	matrix4_mul_id(t_matrix4 const A);
t_matrix4	matrix4_trans(t_matrix4 const A);
void		print_matrix4(t_matrix4 const M);

/* matrix_transform.c */

t_matrix4	matrix4_translate(double x, double y, double z);
t_matrix4	matrix4_scale(double x, double y, double z);
t_matrix4	matrix4_rotate_x(double r);
t_matrix4	matrix4_rotate_y(double r);
t_matrix4	matrix4_rotate_z(double r);
/* t_matrix4	matrix4_shear(double xy, double xz, double yx, double yz,
		double zx, double zy);*/

/* matrix_invert.c */

t_matrix4	matrix4_inv(t_matrix4 const A);

/* matrix_invert_utils.c */

double	matrix3_determinant(t_matrix3 const A);

#endif
