/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:07:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 23:46:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include <math.h>

t_uv	get_planar_map(t_point3 intersect_p)
{
	t_uv	uv;

	uv.u = fmod(intersect_p.x, 1);
	uv.v = fmod(intersect_p.z, 1);
	return (uv);
}
