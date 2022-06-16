/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:46:37 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/16 17:38:00 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "libft.h"
# include <stdbool.h>

/* Enum */

typedef enum e_object_type
{
	T_SPHERE,
	T_PLAN
}			t_object_type;

/* Math related structure */

typedef struct e_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef t_vec	t_vec3d;
typedef t_vec	t_3dpoint;
typedef t_vec	t_2dpoint;
typedef t_vec	t_albedo;
typedef t_vec	t_color;

/* minilibx and program structure */

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	t_image		img;
	void		*ptr;
	void		*win;
}	t_mlx;

typedef struct e_light
{
	t_3dpoint	point;
	double		ratio;
}	t_light;


typedef struct e_scene
{
	t_list	*objs;
	t_light	light;
}				t_scene;

typedef struct s_minirt
{
	t_mlx	mlx;
	t_scene	scene;
}	t_minirt;

/* Related ray structure */

typedef struct e_ray
{
	t_3dpoint	org;
	t_vec3d		dir;
}			t_ray;

typedef struct s_rayhit
{
	double		t;
	t_3dpoint	intersect_p;
	t_vec3d		normal;
	uint32_t	pixel_color;
}	t_rayhit;

/* Primitive geometry structure */

typedef struct e_sphere
{
	t_3dpoint	center;
	double		radius;
}				t_sphere;

typedef struct e_plan
{
	t_3dpoint	point;
	t_vec3d		normal;
}				t_plan;

typedef struct e_object	t_object;

typedef bool (*t_intersect_fnct)(t_object *, t_ray *);

struct e_object
{
	union
	{
		t_sphere	sphere;
		t_plan		plan;
	} p;
	t_albedo			albedo;
	t_rayhit			rayhit;
	t_object_type		type;
	t_intersect_fnct	fnct;
};

#endif
