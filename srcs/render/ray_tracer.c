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

t_color		choose_color(t_env *e)
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

t_color		vp_init(t_env *e, t_camera cam, t_vector vp, t_grid g)
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
		g.ctmp = get_color(e);
	e->skybox = 0;
	return(c_c_add(&g.ctmp, &g.filter));
}

void		stereo_tracer(t_env *e)
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
			g.fblue = vp_init(e, e->lstereo, e->lviewplane, g);
			g.filter = g.red;;
			g.fred = vp_init(e, e->rstereo, e->rviewplane, g);
			g.color = c_c_mult(&g.fblue, &g.fred);
			print_color(&g.color, e, g.x, g.y);
			g.x++;
		}
		g.y++;
	}
}

void		ray_tracer(t_env *e)
{
	t_grid	g;
	
	g.y = 0;
	while (g.y < e->height)
	{
		g.x = e->begin;
		while (g.x < e->fin)
		{
			g.color = vp_init(e, e->camera,
					e->viewplane_point_up_left, g);
			g.x++;
		}
		g.y++;
	}
}
