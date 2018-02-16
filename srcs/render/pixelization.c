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

void		pixel_vp_init(t_pixel *pxl, t_env *e)
{
	pxl->tmpx = pxl->x;
	pxl->tmpy = pxl->y;
	pxl->tmp_vp_pointx = v_double_mult(&e->camera.x_vector, pxl->x);
	pxl->tmp_vp_pointy = v_double_mult(&e->camera.y_vector, pxl->y);
	pxl->viewplane_point = v_v_add(&e->viewplane_point_up_left,
	&pxl->tmp_vp_pointx);
	pxl->viewplane_point = v_v_subs(&pxl->viewplane_point, &pxl->tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&pxl->viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
}

void		pxl_tracer(t_env *e, int sample)
{
	t_pixel		pxl;
	t_color		color;

	pxl.y = 0;
	while (pxl.y < WIN_Y)
	{
		pxl.x = e->begin;
		while (pxl.x < e->fin)
		{
			e->recursion = 6;
			color = set_color(0, 0, 0);
			pixel_vp_init(&pxl, e);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = get_render_mode(e);
			while (pxl.y++ < pxl.tmpy + sample)
			{
				pxl.x = pxl.x != pxl.tmpx ? pxl.x - sample : pxl.x;
				while (pxl.x < pxl.tmpx + sample)
					print_color(&color, e, pxl.x++, pxl.y);
			}
			pxl.y = pxl.tmpy;
		}
		pxl.y += sample;
	}
}
