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
	return (c_c_mult(&c, &filter));
}
