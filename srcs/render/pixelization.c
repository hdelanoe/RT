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

t_pixel		pixel_vp_init(t_pixel *pxl, t_env *e)
{
	t_pixel new;

	new = *pxl;
	new.tmpx = new.x;
	new.tmpy = new.y;
	new.tmp_vp_pointx = v_double_mult(&e->camera.x_vector, new.x);
	new.tmp_vp_pointy = v_double_mult(&e->camera.y_vector, new.y);
	new.viewplane_point = v_v_add(&e->viewplane_point_up_left,
		&new.tmp_vp_pointx);
	new.viewplane_point = v_v_subs(&new.viewplane_point, &new.tmp_vp_pointy);
	return (new);
}

void		pxl_tracer(t_env *e, int sample)
{
	t_pixel		pxl;
	t_color 	color;

	pxl.y = 0;
	while (pxl.y < WIN_Y)
	{
		pxl.x = 0;
		while (pxl.x < WIN_X)
		{
			e->recursion = 6;
			pxl = pixel_vp_init(&pxl, e);
			e->camera.rayon = v_v_subs(&pxl.viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = e->am_flag == 1 ? ambient_occlusion(e) : get_color(e);
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


void		pxl_edit_tracer(t_env *e, int sample)
{
	t_pixel		pxl;
	t_color 	color;

	pxl.y = 0;
	while (pxl.y < WIN_Y)
	{
		pxl.x = 0;
		while (pxl.x < WIN_X)
		{
			e->recursion = 6;
			pxl = pixel_vp_init(&pxl, e);
			e->camera.rayon = v_v_subs(&pxl.viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = e->current_color;
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
