/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:44:52 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/12 13:34:23 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_BONUS_H
# define MATH_UTILS_BONUS_H

# include "minirt_struct_bonus.h"

double		min(double a, double b);
double		max(double a, double b);
bool		fequals(double a, double b);

bool		solve_quadratic(double a, double b, double c, double t[2]);
t_ray		ray_transform(t_ray old_ray, t_matrix4 const M);
t_point3	get_ray_point(t_ray ray, double t);
t_vec3		get_normal(t_object *obj, t_point3 p);
t_vec3		get_reflection_vec(t_vec3 incident, t_vec3 normal);
double		sqr(double a);

#endif
