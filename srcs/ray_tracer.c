/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 18:56:50 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"



void	ray_tracer(t_env *e)
{
	int			x;
	int			y;
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;
	t_color 	color;

	e->in_out = -1;
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			color = set_color(0, 0, 0);
			e->distance = 100000;
			tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
			viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
//				color = get_color(e);
				color = ambient_occlusion(e);
			print_color(&color, e, x, y);
			x++;
		}
		y++;
	}
}
