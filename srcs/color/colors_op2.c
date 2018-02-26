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

t_color		c_double_div(t_color *a, double b)
{
	t_color	new;

	new.b = a->b / b;
	new.g = a->g / b;
	new.r = a->r / b;
	new.b = new.b > 1 ? 1 : new.b;
	new.g = new.g > 1 ? 1 : new.g;
	new.r = new.r > 1 ? 1 : new.r;
	return (new);
}

t_color		c_c_subs(t_color *a, t_color *b)
{
	t_color	color;

	color.b = a->b - b->b;
	color.g = a->g - b->g;
	color.r = a->r - b->r;
	if (color.b < 0)
		color.b = 0;
	if (color.g < 0)
		color.g = 0;
	if (color.r < 0)
		color.r = 0;
	return (color);
}

void		print_color(t_color *color, t_env *e, int x, int y)
{
	if (x >= 0 && x < e->width && y >= 0 && y < e->height)
	{
		e->mlx.data[(x + y * (int)e->width) * 4 + 0] = color->b * 255;
		e->mlx.data[(x + y * (int)e->width) * 4 + 1] = color->g * 255;
		e->mlx.data[(x + y * (int)e->width) * 4 + 2] = color->r * 255;
	}
}

double		get_specular(t_light *light, t_vector *view, t_vector *node)
{
	t_vector	tmp;
	t_vector	r;
	double		reflect;
	double		phong_color;

	reflect = dot_product(&light->rayon, node);
	tmp = v_double_mult(node, 2);
	r = v_double_mult(&tmp, reflect);
	r = v_v_subs(&r, &light->rayon);
	phong_color = 0.2 * powf(dot_product(view, &r), 20) * 3;
	return (phong_color);
}
