/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:09:25 by bsavinel          #+#    #+#             */
/*   Updated: 2022/06/25 12:40:53 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt_struct.h"
#include "ray_intersection.h"
#include "tuple.h"
#include <math.h>
#include "define.h"
#include <stdio.h>

//? https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/

bool	give_intersec_cone(t_object *obj, t_ray *ray, double distance[2])
{
	double	a;
	double	b;
	double	c;
	t_tuple top_org;
	double	cos_square;
	
	top_org = tsub(ray->org, obj->p.cone.top);
	cos_square = pow(cos(DG_RAD(obj->p.cone.angle)), 2);
	a = pow(vec_dot(ray->dir, obj->p.cone.direction), 2) - cos_square;
	b = 2 * (vec_dot(ray->dir, obj->p.cone.direction) * vec_dot(top_org , obj->p.cone.direction) - vec_dot(ray->dir, tmul_scalar(top_org, cos_square)));
	c = pow(vec_dot(top_org, obj->p.cone.direction), 2) - vec_dot(top_org, tmul_scalar(top_org, cos_square));
	return(solve_quadratic(a, b, c, distance));
}