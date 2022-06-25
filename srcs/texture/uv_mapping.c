/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:07:40 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/25 22:11:01 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"

t_uv	get_planar_map(t_point3 intersect_p)
{
	t_uv	uv;

	uv.u = (int) intersect_p.x % 1;
	uv.v = (int) intersect_p.y % 1;
	return (uv);
}
