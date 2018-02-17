/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/02/17 17:17:55 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	get_render_mode(t_env *e)
{
	t_color new;

	if (e->am_flag == 1 && !e->edit_flag)
		new = ambient_occlusion(e);
	else if (e->render_mode == 3 && !e->edit_flag)
		new = cel_shade_color(e);
	else if (e->area_light_on == 1)
		new = get_area_color(e);
	else
		new = get_color(e);
	return (new);
}

t_color	vp_init(t_env *e, t_camera cam, t_vector vp, t_grid g)
{
	e->recursion = 6;
	g.ctmp = set_color(0, 0, 0);
	g.vpx = v_double_mult(&cam.x_vector, g.x);
	g.vpy = v_double_mult(&cam.y_vector, g.y);
	g.vp_point = v_v_add(&vp, &g.vpx);
	g.vp_point = v_v_subs(&g.vp_point, &g.vpy);
	cam.rayon = v_v_subs(&g.vp_point, &cam.origin);
	cam.rayon = normalize(&cam.rayon);
	if (cast_ray(e, cam.rayon, cam.origin))
		g.ctmp = get_render_mode(e);
	e->skybox = 0;
	return (c_c_add(&g.ctmp, &g.filter));
}

void	stereo_tracer(t_env *e)
{
	t_grid	g;

	g.blue = set_color(1, 1, 0);
	g.red = set_color(0, 0, 1);
	g.y = 0;
	while (g.y < e->height)
	{
		g.x = 0;
		while (g.x < e->width)
		{
			g.filter = g.blue;
			g.fblue = vp_init(e, e->lstereo, e->lviewplane, g);
			g.filter = g.red;
			g.fred = vp_init(e, e->rstereo, e->rviewplane, g);
			g.color = c_c_mult(&g.fblue, &g.fred);
			print_color(&g.color, e, g.x, g.y);
			g.x++;
		}
		g.y++;
	}
}

void	ray_tracer(t_env *e)
{
	t_grid g;

	g.filter = set_color(0, 0, 0);
	g.y = e->begin;
	while (g.y < e->fin)
	{
		g.x = 0;
		while (g.x < e->width)
		{
			g.color = vp_init(e, e->camera, e->viewplane_point_up_left, g);
			g.color = set_filter(e, g.color);
			print_color(&g.color, e, g.x, g.y);
			g.x++;
		}
		g.y++;
	}
}
