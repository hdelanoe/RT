/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:21:55 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/01/20 14:21:56 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	custom2(t_color *c)
{
	t_color filter;

	filter.r = (0.852 * c->r) + (0.206 * c->g) + (0.404 * c->b);
	filter.g = (0.700 * c->r) + (0.247 * c->g) + (0.427 * c->b);
	filter.b = (0.90201 * c->r) + (0.392 * c->g) + (0.552 * c->b);
	filter.r = filter.r > 1 ? 1 : filter.r;
	filter.g = filter.g > 1 ? 1 : filter.g;
	filter.b = filter.b > 1 ? 1 : filter.b;
	return (filter);
}

t_color	custom(t_color *c)
{
	t_color filter;

	filter.r = (0.142 * c->r) + (0.349 * c->g) + (0.692 * c->b);
	filter.g = (0.123 * c->r) + (0.471 * c->g) + (0.789 * c->b);
	filter.b = (0.296 * c->r) + (0.302 * c->g) + (0.973 * c->b);
	filter.r = filter.r > 1 ? 1 : filter.r;
	filter.g = filter.g > 1 ? 1 : filter.g;
	filter.b = filter.b > 1 ? 1 : filter.b;
	return (filter);
}

t_color	sepia(t_color *c)
{
	t_color filter;

	filter.r = (0.393 * c->r) + (0.769 * c->g) + (0.189 * c->b);
	filter.g = (0.349 * c->r) + (0.686 * c->g) + (0.168 * c->b);
	filter.b = (0.272 * c->r) + (0.534 * c->g) + (0.131 * c->b);
	filter.r = filter.r > 1 ? 1 : filter.r;
	filter.g = filter.g > 1 ? 1 : filter.g;
	filter.b = filter.b > 1 ? 1 : filter.b;
	return (filter);
}

t_color	set_filter(t_env *e, t_color c)
{
	t_color filter;
	double	equ;

	if (e->filter_flag == 0)
		filter = set_color(1, 1, 1);
	if (e->filter_flag == 1)
		filter = set_color(1, 0, 0);
	if (e->filter_flag == 2)
		filter = set_color(0, 1, 1);
	if (e->filter_flag == 3)
		filter = set_color(0.5, 1, 0.5);
	if (e->filter_flag == 4)
	{
		equ = c.r + c.g + c.b;
		return (set_color(equ / 3, equ / 3, equ / 3));
	}
	if (e->filter_flag == 5)
		return (sepia(&c));
	if (e->filter_flag == 6)
		return (custom(&c));
	if (e->filter_flag == 7)
		return (custom2(&c));
	return (c_c_mult(&c, &filter));
}
