/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:55:04 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/23 18:31:59 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		c_double_mult(t_color *a, double b)
{
	t_color	color;

	color.b = a->b * b;
	color.g = a->g * b;
	color.r = a->r * b;
	return (color);
}

void		print_color(t_color *color, t_env *e, int x, int y)
{
	if (x > 0 && x < WIN_X && y > 0 && y < WIN_Y)
	{
		e->mlx.data[(x + y * WIN_X) * 4 + 0] = color->b * 255;
		e->mlx.data[(x + y * WIN_X) * 4 + 1] = color->g * 255;
		e->mlx.data[(x + y * WIN_X) * 4 + 2] = color->r * 255;
	}
}