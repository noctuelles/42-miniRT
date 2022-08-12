/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:33:24 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/10 18:11:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct_bonus.h"
#include "math.h"
#include "matrix_bonus.h"
#include "texture_bonus.h"
#include "tuple_bonus.h"

static inline t_matrix4	build_tbn_matrix(t_vec3 world_normal)
{
	t_matrix4	tbn;
	t_vec3		t;
	t_vec3		b;

	t = vec_cross(world_normal, vector(0, 1, 0));
	if (vec_mag(t) == 0.)
		t = vec_cross(world_normal, vector(0, 0, 1));
	t = vec_norm(t);
	b = vec_norm(vec_cross(world_normal, t));
	tbn.m[0][0] = t.x;
	tbn.m[1][0] = t.y;
	tbn.m[2][0] = t.z;
	tbn.m[0][1] = b.x;
	tbn.m[1][1] = b.y;
	tbn.m[2][1] = b.z;
	tbn.m[0][2] = world_normal.x;
	tbn.m[1][2] = world_normal.y;
	tbn.m[2][2] = world_normal.z;
	return (tbn);
}

void	perturb_normal(t_texture texture, t_rayhit *rayhit)
{
	rayhit->normal = vec_norm(
			matrix4_tmul(build_tbn_matrix(rayhit->normal),
				get_image_normal(texture, rayhit->uv)));
}
