/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:06:14 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/12 13:35:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "minirt_struct.h"

/*
 *	extract_utils.c
 */

bool	extract_double_pos(t_list **lexer, double *dbl);
bool	extract_double_range(t_list **lexer, double *dbl, double min,
			double max);
bool	extract_texture(t_minirt *minirt, t_list **lexer, t_object *obj,
			t_object_type type);

/*
 *	extract_utils2.c
 */

bool	extract_point(t_list **lexer, t_point3 *place);
bool	extract_vector_norm(t_list **lexer, t_vec3 *vect);
bool	extract_color(t_list **lexer, uint32_t *color);

/*
 *	extract_obejct.c
 */

void	extract_sphere(t_minirt *minirt, t_list **lexer);
void	extract_plan(t_minirt *minirt, t_list **lexer);
void	extract_cylinder(t_minirt *minirt, t_list **lexer);
void	extract_cone(t_minirt *minirt, t_list **lexer);

/*
 *	extract_obejct2.c
 */

void	extract_camera(t_minirt *minirt, t_list **lexer);
void	extract_light(t_minirt *minirt, t_list **lexer);
void	extract_ambiante_light(t_minirt *minirt, t_list **lexer);

/*
 *	parsing.c
 */

void	bad_exit_msg(t_minirt *minirt, char *str, char *tok);
bool	parser(t_minirt *minirt, char *filename);
bool	ft_isdouble(char *str);

#endif
