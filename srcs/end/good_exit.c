/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:55:48 by bsavinel          #+#    #+#             */
/*   Updated: 2022/08/10 21:50:25 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_struct.h"
#include "mlx_utils.h"
#include "libft.h"
#include "minirt_lexer.h"
#include <stdlib.h>
#include <stdio.h>

int	good_exit(t_minirt *backpack)
{
	destruct_mlx(&backpack->mlx);
	ft_lstclear(&backpack->start_lexer, &free);
	exit(0);
	return (0);
}
