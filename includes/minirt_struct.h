/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:46:37 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/08 16:42:46 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "libft.h"
# include "define.h"
# include <pthread.h>
# include <stdbool.h>

/* ############################## Enumerations ############################## */

typedef enum e_object_type
{
	T_SPHERE,
	T_SPHERE_SKYBOX,
	T_PLAN,
	T_CYLINDER
}			t_object_type;

typedef enum e_texture_type
{
	TX_NONE,
	TX_CHECKER,
	TX_IMAGE,
	TX_IMAGEW_NMAP,
	TX_FAILED
}			t_texture_type;

/* ################################# Tuple ################################## */

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_tuple;

typedef struct	s_uv
{
	double	u;
	double	v;
}				t_uv;

typedef t_tuple	t_vec3;
typedef t_tuple	t_point2;
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

typedef struct s_cylinder
{
	t_point3	pos;
	double half_height;
	double diameter;
}				t_cylinder;

typedef struct s_light
{
	t_point3	pos;
	t_color		color;
	double		intensity;
}				t_light;

typedef struct s_scene
{
	t_list	*objs;
	t_list	*light;
	t_light	amb_light;
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

typedef struct s_minirt t_minirt;

typedef struct s_worker
{
	t_minirt		*minirt;
	pthread_t		pthread;
	unsigned int	id;
	unsigned int	assigned_start;
	unsigned int	assigned_end;
}				t_worker;

/* ################################ Program ################################# */

typedef struct	s_camera
{
	t_matrix4	transform;
	size_t		screen_width;
	size_t		screen_height;
	double		aspect_ratio;
	double		scalar_fov;
	t_vec3		look;
	t_point3	from;
}	t_camera;

struct s_minirt
{
	t_mlx		mlx;
	t_scene		scene;
	t_camera	camera;
	t_worker	workers[THREAD_NBR];
};

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
	t_point3	intersect_p_local;
	t_vec3		eyev;
	t_vec3		lightv;
	t_vec3		nlightv;
	double		mag_sqr_lightv;
	t_uv		uv;
	t_vec3		normal;
	t_color		pcolor;
}	t_rayhit;

typedef struct s_object	t_object;

typedef bool (*t_intersect_fnct)(t_object *, t_ray *, t_rayhit *);
typedef t_uv (*t_uvmap_fnct)(t_point3);

typedef struct s_texture
{
	t_image			texel;
	t_image			nmap;
	t_texture_type	type;
	t_color			checker_color[2];
	int				width;
	int				height;
	int				nwidth;
	int				nheight;
}				t_texture;

struct s_object
{
	union
	{
		t_sphere	sphere;
		t_plan		plan;
		t_cylinder	cylinder;
	} p;
	t_rayhit			rayhit;
	t_matrix4			M;
	t_matrix4			M_inv;
	t_matrix4			M_inv_trans;
	t_albedo			albedo;
	t_texture			texture;
	t_object_type		type;
	t_intersect_fnct	fnct;
	t_uvmap_fnct		uvmap_fnct;
};

#endif
