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

t_color	choose_color(t_env *e)
{
	t_color new;

	if (e->aa_flag == 1 && e->pixelize == 0)
	{
		if (e->cel_shade == 1)
			new = e->current_color;
		else
			new = get_color(e);
	}
	else if (e->pixelize == 1)
	{
		if (e->edit_flag == 1)
			new = e->current_color;
		else if (e->cel_shade == 1)
			new = cel_shade_color(e);
		else
			new = get_color(e);
	}
	else if (e->edit_flag == 1)
		new = e->current_color;
	else if (e->cel_shade == 1)
		new = cel_shade_color(e);
	else
		new = get_color(e);
	return (new);
}

t_color stereo_init(t_env *e, t_camera cam, t_vector vp, t_grid g)
{
	e->recursion = 6;
	g.ctmp = set_color(0, 0, 0);
	g.tmp_vp_pointx = v_double_mult(&cam.x_vector, g.x);
	g.tmp_vp_pointy = v_double_mult(&cam.y_vector, g.y);
	g.viewplane_point = v_v_add(&vp, &g.tmp_vp_pointx);
	g.viewplane_point = v_v_subs(&g.viewplane_point, &g.tmp_vp_pointy);
	cam.rayon = v_v_subs(&g.viewplane_point, &cam.origin);
	cam.rayon = normalize(&cam.rayon);
	if (cast_ray(e, cam.rayon, cam.origin))
		g.ctmp = get_color(e);
	return(c_c_add(&g.ctmp, &g.filter));
}

void	stereo_tracer(t_env *e)
{
	t_grid		g;
	
	g.blue = set_color(1, 1, 0);
	g.red = set_color(0, 0, 1);
	g.y = 0;
	while (g.y < e->height)
	{
		g.x = 0;
		while (g.x < e->width)
		{
			g.filter = g.blue;
			g.fblue = stereo_init(e, e->lstereo, e->lviewplane, g);
			g.filter = g.red;;
			g.fred = stereo_init(e, e->rstereo, e->rviewplane, g);
			g.color = c_c_mult(&g.fblue, &g.fred);
			print_color(&g.color, e, g.x, g.y);
			g.x++;
		}
		g.y++;
	}
}

void	ray_tracer(t_env *e)
{
	int			x;
	int			y;
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;
	t_color 	color;
	
	y = 0;
	while (y < e->height)
	{
		x = e->begin;
		while (x < e->fin)
		{
			e->recursion = 6;
			color = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
			viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = get_render_mode(e);
			color = set_filter(e, color);
			print_color(&color, e, x, y);
			e->skybox = 0;
			x++;
		}
		y++;
	}
}
