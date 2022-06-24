/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:46:37 by plouvel           #+#    #+#             */
/*   Updated: 2022/06/24 18:02:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "libft.h"
# include <stdbool.h>

/* ############################## Enumerations ############################## */

typedef enum e_object_type
{
	T_SPHERE,
	T_PLAN
}			t_object_type;

/* ################################# Tuple ################################## */

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_tuple;

typedef t_tuple	t_vec3;
typedef t_tuple	t_point3;
typedef t_tuple	t_color;
typedef t_tuple	t_albedo;

/* ################################# Matrix ################################# */

typedef struct	s_matrix4
{
	double	m[4][4];
}				t_matrix4;

typedef struct	s_matrix3
{
	double	m[3][3];
}				t_matrix3;

typedef struct	s_matrix2
{
	double	m[2][2];
}				t_matrix2;

/* ############################# Object & Scene ############################# */

typedef struct s_sphere
{
	t_point3	pos;
	double		radius;
}				t_sphere;

typedef struct s_plan
{
	t_point3	pos;
	t_vec3		normal;
}				t_plan;

typedef struct s_light
{
	t_point3	pos;
	double		intensity;
}				t_light;

typedef struct s_scene
{
	t_list	*objs;
	t_light	light;
}				t_scene;

/* ################################ Minilibx ################################ */

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
}				t_mlx;

/* ################################ Program ################################# */

typedef struct s_minirt
{
	t_mlx	mlx;
	t_scene	scene;
}	t_minirt;

/* ################################## Ray ################################### */

typedef struct s_ray
{
	t_point3	org;
	t_vec3		dir;
}			t_ray;

typedef struct s_rayhit
{
	double		t;
	t_point3	intersect_p;
	t_vec3		normal;
	uint32_t	pixel_color;
}	t_rayhit;

typedef struct s_object	t_object;

typedef bool (*t_intersect_fnct)(t_object *, t_ray *, t_rayhit *);

struct s_object
{
	union
	{
		t_sphere	sphere;
		t_plan		plan;
	} p;
	t_matrix4			M;
	t_matrix4			M_inv;
	t_albedo			albedo;
	t_object_type		type;
	t_intersect_fnct	fnct;
};

#endif
