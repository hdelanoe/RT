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

void		anti_aliasing_clr_merge(t_color *anti, t_color *clr)
{
	anti->r += clr->r;
	anti->g += clr->g;
	anti->b += clr->b;
}

t_color		get_render_mode(t_env *e)
{
	t_color new;

	if (e->render_mode == 1 && !e->edit_flag)
		new = ambient_occlusion(e);
	else if (e->render_mode == 3 && !e->edit_flag)
		new = cel_shade_color(e);
	else if (e->area_light_on == 1)
		new = get_area_color(e);
	else
		new = get_color(e);
	return (new);
}

t_grid		antialias_loop_init(t_grid *anti, t_env *e, int sample)
{
	t_grid			new;
	t_color			color;

	new = *anti;
	new.xx = 0;
	while (new.xx < sample)
	{
		color = set_color(0, 0, 0);
		new.vpx = v_double_mult(&e->camera.x_vector, new.x + new.xx);
		new.vpy = v_double_mult(&e->camera.y_vector, new.y + new.xx);
		new.vp_point = v_v_add(&e->viewplane_point_up_left,
		&new.vpx);
		new.vp_point = v_v_subs(&new.vp_point,
		&new.vpy);
		e->camera.rayon = v_v_subs(&new.vp_point, &e->camera.origin);
		e->camera.rayon = normalize(&e->camera.rayon);
		if (cast_ray(e, e->camera.rayon, e->camera.origin))
			color = get_render_mode(e);
		anti_aliasing_clr_merge(&new.color, &color);
		new.xx += 0.25;
	}
	return (new);
}

void		aa_tracer(t_env *e, int sample)
{
	t_grid	aa;

	aa.y = 0;
	while (aa.y < WIN_Y)
	{
		aa.x = e->begin;
		while (aa.x < e->fin)
		{
			aa.xx = 0;
			aa.color = set_color(0, 0, 0);
			while (aa.xx < sample)
			{
				aa = antialias_loop_init(&aa, e, sample);
				aa.xx += 0.25;
			}
			aa.color = c_double_div(&aa.color, 16);
			if (aa.color.r != 0 || aa.color.g != 0 || aa.color.b != 0)
				print_color(&aa.color, e, aa.x, aa.y);
			aa.x++;
		}
		aa.y++;
	}
}
