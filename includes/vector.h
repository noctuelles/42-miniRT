/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:45:46 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/16 16:40:00 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "minirt_struct.h"

t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec u, t_vec v);
t_vec	vec_sub(t_vec u, t_vec v);
t_vec	vec_mul_scalar(t_vec u, double scalar);
double	vec_dot(t_vec u, t_vec v);
double	vec_length(t_vec a);
t_vec	vec_normalize(t_vec a);
void	vec_normalize_p(t_vec *a);
double	vec_lenght_p(t_vec a);
void	vec_print(t_vec a);

#endif
