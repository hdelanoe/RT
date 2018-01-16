/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/23 17:58:26 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

pthread_mutex_t mutex0 = PTHREAD_MUTEX_INITIALIZER;

void		*aa_tracer_void(void *e)
{
	aa_tracer(e, 1);
	return ((void *)(1));
}

void		anti_aliasing_clr_merge(t_color *anti, t_color *clr)
{
	anti->r += clr->r;
	anti->g += clr->g;
	anti->b += clr->b;
}

t_anti_a	antialias_loop_init(t_anti_a *anti, t_env *e, int sample)
{
	t_anti_a new;
	t_color 	color;

	new = *anti;
	new.x1 = 0;
	while (new.x1 < sample)
	{
		color = set_color(0, 0, 0);
		e->distance = 100000;
		new.tmp_vp_pointx = v_double_mult(&e->camera.x_vector, new.x + new.x1);
		new.tmp_vp_pointy = v_double_mult(&e->camera.y_vector, new.y + new.y1);
		new.viewplane_point = v_v_add(&e->viewplane_point_up_left,
		&new.tmp_vp_pointx);
		new.viewplane_point = v_v_subs(&new.viewplane_point,
		&new.tmp_vp_pointy);
		e->camera.rayon = v_v_subs(&new.viewplane_point, &e->camera.origin);
		e->camera.rayon = normalize(&e->camera.rayon);
		if (cast_ray(e, e->camera.rayon, e->camera.origin))
			color = e->am_flag == 1 ? ambient_occlusion(e) :get_color(e);
		anti_aliasing_clr_merge(&new.aaclr, &color);
		new.x1 += 0.25;
	}
	return (new);
}

void		aa_tracer(t_env *e, int sample)
{
	t_anti_a	aa;

	e->in_out = -1;
	aa.y = 0;
	// pthread_mutex_lock(&mutex0);
	while (aa.y < WIN_Y)
	{
		aa.x = e->begin;
		while (aa.x < e->fin)
		{
			aa.y1 = 0;
			aa.aaclr = set_color(0, 0, 0);
			while (aa.y1 < sample)
			{
				aa = antialias_loop_init(&aa, e, sample);
				aa.y1 += 0.25;
			}
			aa.aaclr = c_double_div(&aa.aaclr, 16);
			print_color(&aa.aaclr, e, aa.x, aa.y);
			aa.x++;
		}
		aa.y++;
	}
	// pthread_mutex_unlock(&mutex0);
}
