/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/23 17:58:26 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		pixel_vp_init(t_grid *g, t_env *e)
{
	g->xx = g->x;
	g->yy = g->y;
	g->tmp_vp_pointx = v_double_mult(&e->camera.x_vector, g->x);
	g->tmp_vp_pointy = v_double_mult(&e->camera.y_vector, g->y);
	g->viewplane_point = v_v_add(&e->viewplane_point_up_left,
	&g->tmp_vp_pointx);
	g->viewplane_point = v_v_subs(&g->viewplane_point, &g->tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&g->viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
}

void		pxl_tracer(t_env *e, int sample)
{
	t_grid		g;
	t_color		color;

	g.y = 0;
	while (g.y < WIN_Y)
	{
		g.x = e->begin;
		while (g.x < e->fin)
		{
			e->recursion = 6;
			color = set_color(0, 0, 0);
			pixel_vp_init(&g, e);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = get_render_mode(e);
			while (g.y++ < g.yy + sample)
			{
				g.x = g.x != g.xx ? g.x - sample : g.x;
				while (g.x < g.xx + sample)
					print_color(&color, e, g.x++, g.y);
			}
			g.y = g.yy;
		}
		g.y += sample;
	}
}
