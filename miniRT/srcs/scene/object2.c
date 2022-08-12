/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:59:02 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/11 18:01:21 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "ray_intersection.h"
#include "mlx_utils.h"
#include "texture.h"
#include "define.h"
#include "matrix.h"
#include "tuple.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

t_matrix4	build_rotation_matrix(t_vec3 orient)
{
	t_matrix4	m;
	double		alpha;
	double		beta;

	alpha = atan2(sqrt(orient.x * orient.x + orient.z * orient.z), orient.y);
	beta = atan2(orient.z, orient.x);
	m = matrix4_rotate_z(-alpha);
	m = matrix4_mul(matrix4_rotate_y(-beta), m);
	return (m);
}

void	apply_obj_transform(t_object *obj, t_matrix4 const M)
{
	obj->m = M;
	obj->m_inv = matrix4_inv(M);
}
